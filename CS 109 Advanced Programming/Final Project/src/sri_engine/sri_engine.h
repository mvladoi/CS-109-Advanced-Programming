#ifndef SRI_SRI_ENGINE_H
#define SRI_SRI_ENGINE_H

#include <string>
#include <vector>
#include <cstdint>
#include <map>
#include <semaphore.h>
#include "../fact/fact.h"
#include "../rule/rule.h"
#include "./table.h"
#include "ThreadManager.h"
using namespace std;





class SRIEngine {

  friend class predicateThread;
  
  private:
    map<string, map<int, Fact *> *> *facts;
    map<string, Rule*> *rules;

    vector<string> stringToVector(string& myString,char delimiter);// function that parse a string by delimiter into a vector


    bool isFact(string factName);
    Fact *isFact(const string &FactName, int numParams);
    map<int, Fact *> * getFactMap(string factName);
    string printFacts();

    bool isRule(string ruleName);
    Rule* getRuleObj(string ruleName);
    string  printRules();
    Table *expandFact(Fact *in_fact, vector<string> params);
    Table *expandRule(Rule *in_rule, vector<string> params);
    void expandOrRule(vector<string> *ruleParams, list<Predicate*> *sortedPredicatesList, Table* masterTable);
    void expandAndRule(vector<string> *queryParams, vector<string> *ruleParams, list<Predicate*> *sortedPredicatesList, Table* masterTable);
    static void fill_subtable(Table &subtable, Table &orig, vector<string> &params, vector<string> &prev_params);
    static void *andThreadFunction(void *p);
    static void createAndThread(ThreadManager *manage, sem_t *parent_sem, Table *orig_table, list<Predicate *>::iterator current_pred_iter, list<Table *>::iterator current_pred_table_iter, list<Predicate *>::iterator pred_end_iter, bool expanded);

  public:
    SRIEngine();
    void createFact(string input); //handles creating new fact list if it doesn't exists, calls fact constructor, etc.
    void createRule(string input);
    void drop(string input);
    string inference(string input);
    string dump_sri();
    ~SRIEngine();
};

#endif
