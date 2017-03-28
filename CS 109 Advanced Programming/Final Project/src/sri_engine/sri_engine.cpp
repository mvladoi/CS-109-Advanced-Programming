#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <semaphore.h>
#include <string>
#include <stack>
#include "./sri_engine.h"
#include <map>
#include "Thread.h"
#include "ThreadManager.h"
#include "predicateThread.h"
#include "andThread.h"

/************************** Prototypes *****************************/
void filterQuery(Table *T, const vector<string> &data, const vector<int> &filteredParams);

static int threadNo = 1;

SRIEngine::SRIEngine()
{
    facts = new map<string, map<int, Fact *> *>;
    rules = new map<string, Rule*>;
}

///////////////////////////////////////////////////////////////
//CREATE FACT
void SRIEngine::createFact(string input)
{
    char delimiter = '/';
    vector<string> temp = stringToVector(input,delimiter); //all the input in a vector of strings
//initialize the variable

    //cout <<input ;
    string factName = temp[0];

    int numberOfParameters;
    stringstream  ss (temp[1]);
    ss >> numberOfParameters;

    vector <string>* factParameters = new vector<string>;
    size_t index = 2;
// check if it has parameters
    if (temp.size() > index)
    {
        for(size_t i = 2 ; i < temp.size(); i++)
        {
            factParameters->push_back(temp[i]);
        }
    }

//Initialize the variables
    Fact* tempFact;

// if the fact does not exist
    if(!isFact(factName))
    {
        tempFact = new Fact(factName);
        tempFact->new_instance(factParameters);
        map<int,Fact*>* innerMap;

        innerMap = new map<int,Fact*>;
        innerMap->insert(make_pair(numberOfParameters, tempFact));

        facts ->insert(make_pair(factName,innerMap));
    }
// if the fact exist
    else
    {
        map<int,Fact*> * factMap = getFactMap(factName);
        map<int, Fact *> ::iterator it;
        it = factMap->find(numberOfParameters);
        //if I add a new instance to the fact with the same nr of parameters
        if(it != factMap->end())
        {
            factMap->at(numberOfParameters)->new_instance(factParameters);
        }
        //if I add a fact with different nr of parameters
        else
        {
            tempFact = new Fact(factName);
            tempFact->new_instance(factParameters);
            factMap->insert(make_pair(numberOfParameters, tempFact));
        }
    }
}

bool SRIEngine::isFact(string factName)
{
    map<string, map<int, Fact *> *> ::iterator it;
    it = facts->find(factName);
    if(it != facts->end())
    {
        return true;
    }
    return false;
}


Fact *SRIEngine::isFact(const string &FactName, int numParams){
  if(isFact(FactName)){
    map<int,Fact*> *factMapPtr = getFactMap(FactName);
    map<int,Fact*> :: iterator it;
    it = factMapPtr->find(numParams);
    if(it!=factMapPtr->end()){
      return factMapPtr->at(numParams);
    }
    else{
      return NULL;
    }
  }
  else{
    return NULL;
  }
}

map<int,Fact*> * SRIEngine::getFactMap(string factName)
{
    map<string, map<int, Fact *> *> ::iterator it;
    it = facts->find(factName);

    return  facts->at(factName);
}

string  SRIEngine::printFacts()
{
   string a = "";
    for( map<string,map<int,Fact*>* >::const_iterator ptr=facts->begin(); ptr!=facts->end(); ptr++)
    {
        for( map<int,Fact*>::const_iterator eptr=ptr->second->begin(); eptr!=ptr->second->end(); eptr++)
        {
           a+=  eptr->second->toString();
        }
    }
    return a;
}

//////////////////////////////////////////////////////
//CREATE RULE
void SRIEngine::createRule(string input)
{
    char delimiter = '/';
    vector<string> temp = stringToVector(input,delimiter);

////////////////////////////////////////////////////////////Vector of strings
    string stringDelimiter = "PRED";

    vector<vector<string>> myVector;
    vector<string> row;
    for( size_t i = 0 ; i < temp.size(); i++)
    {

        if(temp[i] != "PRED")
        {
            row.push_back(temp [i]);
        }

        else
        {
            myVector.push_back(row);
            row.clear();
        }
    }
    myVector.push_back(row);

///////////////////////////////// I have a vectors of vectors
// Foo 1 $X,$Y,$Z
// Baw $X $Y $Z
// Bar $X $Y $Z


    string ruleName = myVector[0][0];
    uint8_t ruleOperation;
    ruleOperation = stoi(myVector[0][1], nullptr, 10);
    vector <string> ruleParameters;

    for(size_t i = 2; i < myVector[0].size(); i++)
    {
        ruleParameters.push_back(myVector[0][i]);
    }

    Rule* newRule;
    if(!isRule(ruleName))
    {
        newRule = new Rule(ruleName);
    }
    else
    {
        newRule = getRuleObj(ruleName);
    }

    newRule->initialize_rule(ruleOperation, ruleParameters);
    
//////////////////////////////////////////////

    vector<string> predicateParameters;

    for(size_t i = 1; i < myVector.size(); i++)
    {
        string predicateName = myVector[i][0];
        for(size_t j =1; j < myVector[i].size(); j++)
        {
            predicateParameters.push_back(myVector[i][j]);

        }
        newRule->add_predicate(predicateName, predicateParameters);///here we need to copy the vector
        predicateParameters.clear();
    }

///////////////////////////////////////////////////////////////

    rules->insert(make_pair(ruleName, newRule));

}

bool SRIEngine::isRule(string ruleName)
{
    map<string,Rule*>::iterator it;//map<string, Rule*> *rules;
    it = rules->find(ruleName);
    if(it != rules->end())
    {
        return true;
    }
    return false;
}

Rule* SRIEngine::getRuleObj(string ruleName)
{
    map<string,Rule*>::iterator it;//map<string, Rule*> *rules;
    it = rules->find(ruleName);
    if(it != rules->end())
        return rules->at(ruleName);

    return nullptr;
}

string SRIEngine::printRules()
{
string a = "";
    for( map<string, Rule*>::const_iterator ptr= rules->begin(); ptr!=rules->end(); ptr++)
    {
        a+= ptr->second->toString();
    }
    return a;
}

void SRIEngine::drop(string inputName)
{
    if(isFact(inputName))
    {
        facts->erase(inputName);
    }
    if(isRule(inputName))
    {
        rules->erase(inputName);
    }
}

string SRIEngine::inference(string input)
{

  // reset thread counter
  Thread::resetThreadCounter();

  std::cout<<"***************************************\n";
  std::cout<<"*            Thread Sequnce           *\n";
  std::cout<<"***************************************\n";
  
  // create a vector for the input inference
  vector<string> data = stringToVector(input, '/');

  // check if it's a non-save inference
  if (data[0] == "0") {
    
    // create a vector for the filtered Parameters
    vector<int> filteredParams;
    
    // store the indices of the filtered Parameters
    for(size_t i = 2; i < data.size(); i++){
      if(data[i][0] != '$'){
	filteredParams.push_back(i);
      }
    }
    
    // check if all parameteres are filtered parameters
    int numParams = data.size() - 2;
    
    
    // get the parameters
    vector<string> params = vector<string>(data.begin() + 2, data.end());

    // check the fact exists
    Fact *workfact = isFact(data[1], data.size() - 2);

    if (workfact != NULL) {
      // expand the fact with given parameters
      Table *T = expandFact(workfact, params);
      T->remove_duplicates();

      // if there are filtered parameters, then filter the table
      if( filteredParams.size() > 0){
	// filter queries
	filterQuery(T,data,filteredParams);

	// check if all parameteres are filtered parameters	
	if(numParams == filteredParams.size()){
	  if( T->size() > 0){
	    return "True";
	  }
	  else{
	    return "False";
	  }
	}
	else{
	  // if Table size is not zero, remove filtered parameter Columns
	  if( T->size() > 0 ){
	    for(int i = 0; i < filteredParams.size(); i++){
	      T->delete_column(data[filteredParams[i]]);
	    }
	  } 
	}
      }
      if( T->size() > 0){
	std::cout<<"***************************************\n";
	std::cout<<"*           Inference Output          *\n";
	std::cout<<"***************************************\n";
	
	return T->toString(params); //TODO
      }
      else{
	return "False";
      }
    }
    
    Rule *workrule = getRuleObj(data[1]);
    if (workrule != NULL) {
      Table *T = expandRule(workrule, params);
      T->remove_duplicates();
            // if there are filtered parameters, then filter the table
      if( filteredParams.size() > 0){
	// filter queries
	filterQuery(T,data,filteredParams);

	// check if all parameteres are filtered parameters	
	if(numParams == filteredParams.size()){
	  if( T->size() > 0){
	    return "True\n";
	  }
	  else{
	    return "False\n";
	  }
	}
	else{
	  // if Table size is not zero, remove filtered parameter Columns
	  if( T->size() > 0 ){
	    for(int i = 0; i < filteredParams.size(); i++){
	      T->delete_column(data[filteredParams[i]]);
	    }
	  } 
	}
      }
      if( T->size() > 0){
	std::cout<<"***************************************\n";
	std::cout<<"*           Inference Output          *\n";
	std::cout<<"***************************************\n";

	return T->toString(params); //TODO
      }
      else{
	return "False";
      }
    }
    return "Non-existent in Fact or Rule.\n";
  }
  else{
    // create a vector for the filtered Parameters
    vector<int> filteredParams;
    
    // store the indices of the filtered Parameters
    for(size_t i = 3; i < data.size(); i++){
      if(data[i][0] != '$'){
	filteredParams.push_back(i);
      }
    }
    
    // check if all parameteres are filtered parameters
    int numParams = data.size() - 3;
    
    
    // get the parameters
    vector<string> params = vector<string>(data.begin() + 3, data.end());

    // check the fact exists
    Fact *workfact = isFact(data[2], data.size() - 3);

    if (workfact != NULL) {
      // expand the fact with given parameters
      Table *T = expandFact(workfact, params);
      T->remove_duplicates();

      // if there are filtered parameters, then filter the table
      if( filteredParams.size() > 0){
	// filter queries
	filterQuery(T,data,filteredParams);

	// check if all parameteres are filtered parameters	
	if(numParams == filteredParams.size()){
	  if( T->size() > 0){
	    string sFact = data[1]+"/"+to_string(filteredParams.size())+"/";
	    for(int i = 0; i < params.size(); i++){
	      sFact += params[i]+"/";
	    }
	    createFact(sFact);
	    return "True and Fact Saved!";
	  }
	  else{
	    return "False";
	  }
	}
	else{
	  // if Table size is not zero, remove filtered parameter Columns
	  if( T->size() > 0 ){
	    for(int i = 0; i < filteredParams.size(); i++){
	      T->delete_column(data[filteredParams[i]]);
	    }
	  } 
	}
      }
      std::cout<<"***************************************\n";
      std::cout<<"*           Inference Output          *\n";
      std::cout<<"***************************************\n";
      
      return T->toString(params); //TODO
    }
    
    Rule *workrule = getRuleObj(data[2]);
    if (workrule != NULL) {
      Table *T = expandRule(workrule, params);
      T->remove_duplicates();
            // if there are filtered parameters, then filter the table
      if( filteredParams.size() > 0){
	// filter queries
	filterQuery(T,data,filteredParams);

	// check if all parameteres are filtered parameters	
	if(numParams == filteredParams.size()){
	  if( T->size() > 0){
	    string sFact = data[1]+"/"+to_string(filteredParams.size())+"/";
	    for(int i = 0; i < params.size(); i++){
	      sFact += params[i]+"/";
	    }
	    createFact(sFact);
	    return "True and Fact Saved!";
	  }
	  else{
	    return "False\n";
	  }
	}
	else{
	  // if Table size is not zero, remove filtered parameter Columns
	  if( T->size() > 0 ){
	    for(int i = 0; i < filteredParams.size(); i++){
	      T->delete_column(data[filteredParams[i]]);
	    }
	  } 
	}
      }

      // check if Table is not empty
      if(T->size() > 0){
	for(int i = 0; i < T->size(); i++){
	  string newFact = data[1]+"/"+to_string(params.size())+"/";
	  for(int j = 0; j < params.size(); j++){
	    string paramName = params[j];
	    newFact += T->get_entry(paramName,i)+"/";
	  }
	  createFact(newFact);
	}
	std::cout<<"***************************************\n";
	std::cout<<"*           Inference Output          *\n";
	std::cout<<"***************************************\n";
	return "Facts Saved!\n";
      }
      else{
	return "No Resulting Facts to Save!\n";
      }
      
    }
    return "Non-existent in Fact or Rule.\n";
  }
}


void filterQuery(Table *T, const vector<string> &data, const vector<int> &filteredParams){
  // iterate over each table entry
  int i = 0;

  bool validEntry = true;
  while( i < T->size()){
    // declare valid entry
    validEntry = true;

    // iterate over the filtered parameters
    for(int j = 0; j < filteredParams.size(); j++){

      // define filtered parameter index
      int filteredParamIndex = filteredParams[j];

      // filtered parameter string
      string filteredParamString = data[filteredParamIndex];
      
      if(filteredParamString.compare(T->get_entry(filteredParamString,i)) != 0){
	validEntry = false;
	break;
      }
    }

    // if valid entry, move to next entry
    if(validEntry){
      i++;
    }
    else{
      T->delete_entry(i);
    }
  }
}

Table *SRIEngine::expandFact(Fact *in_fact, vector<string> params) {
  // create new Table
  Table *T = new Table();

  // get number of instances count
  size_t numInstances = in_fact->num_of_instance();

  // Add each fact instance to the table
  for(size_t i = 0; i < numInstances; i++){
    T->add_entry(params, *((*in_fact)[i]));
  }

  return T;
  
}

Table * SRIEngine::expandRule(Rule *in_rule, vector<string> params) {

  Table *retval = new Table();
  for (size_t i = 0; i < in_rule->get_num_instances(); ++i) {
    if (in_rule->get_operation(i) == OR) {
      //expandOrRule(in_rule->get_rule_param(i), in_rule->get_sorted_instance(i), retval);
      expandOrRule(&params, in_rule->get_sorted_instance(i), retval);
    } else {
      expandAndRule(&params, in_rule->get_rule_param(i), in_rule->get_sorted_instance(i), retval);
    }
  }
  return retval;
}

void SRIEngine::expandOrRule(vector<string> *ruleParams, list<Predicate*> *sortedPredicatesList, Table* masterTable){

  // create a mutex for the master table and printing
  predicateThread::createStaticMutexes();
  
  // define threadManager
  ThreadManager * threadManager = new ThreadManager();
  
  // iterate over predicates
  for(auto it=sortedPredicatesList->begin(); it != sortedPredicatesList->end(); ++it){
    // check if number of parameters matches rule parameters
    if(ruleParams->size() == (*it)->get_param_match()){
      // check if fact
      Fact *workfact = isFact((*it)->get_name(), (*it)->num_params());
      // check if rule
      Rule *workrule = getRuleObj((*it)->get_name());
      if (workfact != NULL) {
	threadManager->addThread(new predicateThread(0,workfact,ruleParams,masterTable,this));
      }
      else if (workrule != NULL) {
	threadManager->addThread(new predicateThread(1,workrule,ruleParams,masterTable,this));
      }
    }
  }

  // start all threads
  threadManager->start();

  // wait for all threads to finish
  threadManager->barrier();
  
  // delete the thread manager
  delete(threadManager);
  
  // iterate over table columns and remove non-matching params
  vector<string> tableColumns = masterTable->get_columns();
  for(auto tableIt=tableColumns.begin(); tableIt != tableColumns.end(); ++tableIt){
    bool found = false;
    for(auto paramIt = ruleParams->begin(); paramIt != ruleParams->end(); paramIt++){
      // it match found, set found = true
      if((*paramIt).compare(*tableIt) == 0){
	found = true;
      }
    }
    // if not found, delete column
    if(!found){
      masterTable->delete_column(*tableIt);
    }
  }

  // destroy master table and print mutexes
  predicateThread::destroyStaticMutexes();
}

void SRIEngine::fill_subtable(Table &subtable, Table &orig, vector<string> &params, vector<string> &prev_params) {
  vector<string> subcolumns = subtable.get_columns();
  vector<string> origcolumns = orig.get_columns();
  vector<string> shared_col = vector<string>();
  for (auto iter = params.begin(); iter != params.end(); ++iter) {
    if (find(subcolumns.begin(), subcolumns.end(), *iter) != subcolumns.end() &&
	find(prev_params.begin(), prev_params.end(), *iter) != prev_params.end()) {
      shared_col.push_back(*iter);
    }
  }
  for (int i = 0; i < (int) orig.size(); ++i) {
    bool addon = true;
    for (auto iter = shared_col.begin(); iter != shared_col.end(); ++iter) {
      if (orig.get_entry(*iter, i).compare(subtable.get_entry(*iter, 0)) != 0) {
	addon = false;
	break;
      }
    }
    if (addon) {
      vector<string> origentry = orig.get_entry_row(origcolumns, i);
      subtable.copy_add_entry(origcolumns, origentry, 0);
    }
  }
  subtable.delete_entry(0);
}

void *SRIEngine::andThreadFunction(void *p) {
  struct parameters {
    ThreadManager *manage;
    sem_t *parent_sem;
    Table *orig_table;
    list<Predicate *>::iterator current_pred_iter;
    list<Table *>::iterator current_pred_table_iter;
    list<Predicate *>::iterator pred_end_iter;
    bool expanded;
  };
  auto manage = ((struct parameters *) p)->manage;
  auto parent_sem = ((struct parameters *) p)->parent_sem;
  auto orig_table = ((struct parameters *) p)->orig_table;
  auto current_pred_iter = ((struct parameters *) p)->current_pred_iter;
  auto current_pred_table_iter = ((struct parameters *) p)->current_pred_table_iter;
  auto pred_end_iter = ((struct parameters *) p)->pred_end_iter;
  bool expanded = ((struct parameters *) p)->expanded;
  int thrd = threadNo++;
  if (!expanded) {
    fill_subtable(*orig_table, *(*current_pred_table_iter), *((*current_pred_iter)->get_param()), *((*prev(current_pred_iter))->get_param()));
  }
  if (next(current_pred_iter) != pred_end_iter && orig_table->size() > 0) {
    vector<Table *> exp_tables = vector<Table *>();
    sem_t loop_semaphore;
    sem_init(&loop_semaphore, 0, 4);
    for (int i = 0; i < orig_table->size(); ++i) {
      exp_tables.push_back(orig_table->get_entry_subtable(i));
      sem_wait(&loop_semaphore);
      createAndThread(manage, &loop_semaphore, exp_tables[i], next(current_pred_iter), next(current_pred_table_iter), pred_end_iter, false);
    }
    for (int i = 0; i < 4; ++i) {
      sem_wait(&loop_semaphore);
    }
    for (int i = 0; i < 4; ++i) {
      sem_post(&loop_semaphore);
    }
    {
      int i = 0;
      for (auto iter = exp_tables.begin(); iter != exp_tables.end(); ++iter) {
	i = orig_table->replace_entry(i, *(*iter));
	++i;
      }
    }
  }
  free(p);
  sem_post(parent_sem);
}

void SRIEngine::createAndThread(ThreadManager *manage, sem_t *parent_sem, Table *orig_table, list<Predicate *>::iterator current_pred_iter, list<Table *>::iterator current_pred_table_iter, list<Predicate *>::iterator pred_end_iter, bool expanded) {
  struct parameters {
    ThreadManager *manage;
    sem_t *parent_sem;
    Table *orig_table;
    list<Predicate *>::iterator current_pred_iter;
    list<Table *>::iterator current_pred_table_iter;
    list<Predicate *>::iterator pred_end_iter;
    bool expanded;
  };
  struct parameters *param = (struct parameters *) malloc(sizeof(struct parameters));
  param->manage = manage;
  param->parent_sem = parent_sem;
  param->orig_table = orig_table;
  param->current_pred_iter = current_pred_iter;
  param->current_pred_table_iter = current_pred_table_iter;
  param->pred_end_iter = pred_end_iter;
  param->expanded = expanded;
  andThread *thread = new andThread(andThreadFunction, (void *) param);
  thread->start();
  manage->addThread(thread);
}

void SRIEngine::expandAndRule(vector<string> *queryParams, vector<string> *ruleParams, list<Predicate*> *sortedPredicatesList, Table* masterTable) {
  auto pred_list = list<Predicate *>();
  auto pred_tables = list<Table *>();
  andThread::createMutex();
  /* expand rules and facts into tables and add them to the pred lists. */
  for (auto iter = sortedPredicatesList->begin(); iter != sortedPredicatesList->end(); ++iter){
    Fact *workfact = isFact((*iter)->get_name(), (*iter)->num_params());
    Rule *workrule = getRuleObj((*iter)->get_name());
    if (workfact != NULL) {
      pred_tables.push_back(expandFact(workfact, *((*iter)->get_param())));
    } else if (workrule != NULL) {
      pred_tables.push_back(expandRule(workrule, *((*iter)->get_param())));
    } else {
      continue;
    }
    pred_list.push_back(*iter);
  }
  /* push first list onto the subtable stack--use as base table */
  auto pred_list_iter = pred_list.begin();
  auto pred_tables_iter = pred_tables.begin();
  Table workTable = Table();
  workTable.cat(*(*(pred_tables.begin())));
  ThreadManager *thread_track = new ThreadManager();
  sem_t dummy;
  sem_init(&dummy, 0, 1);
  sem_wait(&dummy);
  createAndThread(thread_track, &dummy, &workTable, pred_list.begin(), pred_tables.begin(), pred_list.end(), true);
  sem_wait(&dummy);
  sem_post(&dummy);
  delete thread_track;
  andThread::destroyMutex();
  /* delete columns not called for by the rule */
  vector<string> tableColumns = workTable.get_columns();
  for(auto tableIt=tableColumns.begin(); tableIt != tableColumns.end(); ++tableIt){
    bool found = false;
    for(auto paramIt = ruleParams->begin(); paramIt != ruleParams->end(); paramIt++){
      if((*paramIt).compare(*tableIt) == 0){
	found = true;
	break;
      }
    }
    // if not found, delete column
    if(!found){
      workTable.delete_column(*tableIt);
    }
  }
  /* rename columns to match params specified by the query */
  {
    auto ruleIt = ruleParams->begin();
    auto queryIt = queryParams->begin();
    while (queryIt != queryParams->end()) {
      workTable.move_column(*queryIt, *ruleIt);
      ++ruleIt;
      ++queryIt;
    }
  }
  masterTable->cat(workTable);
}

string SRIEngine::dump_sri()
{
 return  printFacts() + printRules();
}

SRIEngine::~SRIEngine()
{
    delete facts;
    delete rules;
}

vector<string> SRIEngine::stringToVector(string& str,char delimiter)
{
    vector<std::string> vec;
    string element;

    //we are going to loop through each character of the string slowly building an element string.
    //whenever we hit a delimiter, we will push the element into the vector, and clear it to get ready for the next element
    for_each(begin(str),end(str),[&](char const ch)
    {
        if(ch!=delimiter)
        {
            element+=ch;
        }
        else
        {
            if (element.length()>0)
            {
                vec.push_back(element);
                element.clear();
            }
        }
    });

    //push in the last element if the string does not end with the delimiter
    if (element.length()>0)
    {
        vec.push_back(element);
    }

    return vec;
}
