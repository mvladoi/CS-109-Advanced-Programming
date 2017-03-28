#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "./sri_engine/sri_engine.h"

#define RULE_NAME_POS 1
#define RULE_TYPE_POS 2
#define RULE_FIRST_PRED_POS 3
#define INFERENCE_SAVE_LENGTH 3
#define INFERENCE_POS 1
#define SAVED_FACT_POS 2
using namespace std;


/**************** Prototypes *********************/
void handleCommand(const string &command, SRIEngine *SRI);
vector<string> *splitString(const string &str, const char &delim);
void vecToString(vector<string> &vec);
void loadSriFile(const string &inFileName, SRIEngine* SRI);
string parseRule(vector<string> &ruleVec);
string parseFact(const string &factStr);
string parseInference(vector<string> &infVec);
void parseParams(vector<string> *paramVec, const string &paramStr);
void parseAndAddRulePred(string &parsedRule, const string &Pred);
void writeToFile(const string &outputFileName,const string &outputText);
/**************** main() *********************/
int main(){

  SRIEngine SRI;

  while(true){
    
    // define input string
    string input;
    
    // print out prolog style command prompt
    cout<<"| ?- ";

    // take in input
    getline(cin, input);

    // if exit, then close program
    if(!input.compare("exit")){
      break;
    }
    // if not endline
    else if(input.compare("")){
      // handle command
      handleCommand(input,&SRI);
    }
  }

  return 0;
}


/**************** handleCommand() *********************/
void handleCommand(const string &command, SRIEngine *SRI){
  
  // define token delimeter
  char delim = ' ';
  
  // split string into tokens and put them into vectors
  vector<string> *splitComm = splitString(command,delim);

  // get command keyword
  string keyword = (*splitComm)[0];

  
  // if LOAD
  if(!keyword.compare("LOAD")){
    string inputFileName = (*splitComm)[1];
    loadSriFile(inputFileName, SRI);
  }
  // if FACT
  else if(!keyword.compare("FACT")){
    string factStr = (*splitComm)[1];
    SRI->createFact(parseFact(factStr));
  }
  // if RULE
  else if(!keyword.compare("RULE")){
    SRI->createRule(parseRule(*splitComm));
  }
  
  // if INFERENCE
  else if(!keyword.compare("INFERENCE")){
    cout<<SRI->inference(parseInference(*splitComm))<<endl;
  }
  // if DROP
  else if(!keyword.compare("DROP")){
    string FactOrRuleName = (*splitComm)[1];
    SRI->drop(FactOrRuleName);
  }
  // if DUMP
  else if(!keyword.compare("DUMP")){
    string outputFileName = (*splitComm)[1];
    writeToFile(outputFileName,SRI->dump_sri());
  }
  else{
    cout<<"handleCommand() Error: Unknown Keyword\n";
  }
  delete(splitComm);
}


/**************** splitString() *********************/
vector<string> *splitString(const string &str,const char &delim){
  // define pointer to split string vector
  vector<string> *splitStrVec = new vector<string>();
  
  // define string stream
  istringstream strStream(str);

  // define token
  string token;

  // populate vector with tokens
  while(getline(strStream, token, delim)){
      splitStrVec->push_back(token);
  }
  return splitStrVec;
}



/**************** loadSriFile() *********************/
void loadSriFile(const string &inFileName, SRIEngine* SRI){
  // create input file handler
  ifstream infile(inFileName);

  // if file opens
  if(infile.is_open()){
    //cout<<"File Open\n";
    string line;
    while(!infile.eof()){
      // get next line
      getline(infile,line);

      // if neither comment nor endline, handle command
      if(line[0]!='#' && line.compare("")){
	handleCommand(line,SRI);
      }
    }

    infile.close();
  }
  // print error message
  else{
    cout<<"Error loadSriFile: Cannot open file: "<<inFileName<<"\n";
  }
  
}

/************* parseInference() ********************/
string parseInference(vector<string> &infVec){
  // create empty string
  string parsedInference = "";

  // check if inference is to be stored or not, 1 = store, 0 = don't store
  if( infVec.size() >= INFERENCE_SAVE_LENGTH && infVec[SAVED_FACT_POS][0] != '#'){
    parsedInference += "1/" + infVec[SAVED_FACT_POS] + "/";
  }
  else{
    parsedInference += "0/";
  }

  // get position of left and right parens
  size_t param_start_pos = infVec[INFERENCE_POS].find("(");
  size_t param_end_pos = infVec[INFERENCE_POS].find(")");
  
  // store infName
  size_t start = 0;
  size_t count = param_start_pos;
  string InfName = infVec[INFERENCE_POS].substr(start,count);

  // paramStr
  start = param_start_pos+1;
  count = param_end_pos-param_start_pos-1;
  string paramStr = infVec[INFERENCE_POS].substr(start,count);


  // define a vector of strings for parameters
  vector<string> paramVec;

  // parse Params into a vector
  parseParams(&paramVec, paramStr);

  // add Inference name and params to parsedInference
  parsedInference += InfName+"/";
  
  // add params to parsed fact
  for(vector<string>::iterator it = paramVec.begin(); it != paramVec.end(); ++it){
   parsedInference += *it + "/";
  }

  return parsedInference;
}

/************* parseFact() ********************/
string parseFact(const string &factStr){
  // define empty parsed fact
  string parsedFact = "";

  // get position of left and right parens
  size_t param_start_pos = factStr.find("(");
  size_t param_end_pos = factStr.find(")");
  
  // store factName
  size_t start = 0;
  size_t count = param_start_pos;
  string factName = factStr.substr(start,count);

  // paramStr
  start = param_start_pos+1;
  count = param_end_pos-param_start_pos-1;
  string paramStr = factStr.substr(start,count);

  // define a vector of strings for parameters
  vector<string> paramVec;

  // parse Params into a vector
  parseParams(&paramVec, paramStr);

  // add fact name and num of params to parsed fact
  parsedFact = factName + "/" + to_string(paramVec.size()) + "/";
  
  // add params to parsed fact
  for(vector<string>::iterator it = paramVec.begin(); it != paramVec.end(); ++it){
   parsedFact += *it + "/";
  }
  
  return parsedFact;
}



/************* parseRule() ********************/
string parseRule(vector<string> &ruleVec){
  // store ruleName
  size_t param_start_pos = ruleVec[RULE_NAME_POS].find("(");
  size_t param_end_pos = ruleVec[RULE_NAME_POS].find(")");
  size_t start = 0;
  size_t count = param_start_pos;
  string parsedRule = ruleVec[RULE_NAME_POS].substr(start,count) + "/";

  // add logic operator
  if(!ruleVec[RULE_TYPE_POS].compare("AND")){
    parsedRule += "1/";
  }
  else{
    parsedRule += "0/";
  }

  // add LHS params
  start = param_start_pos+1;
  count = param_end_pos-param_start_pos-1;
  string LHSparamStr = ruleVec[RULE_NAME_POS].substr(start,count);

   // define a vector of strings for parameters
  vector<string> paramVec;

  // parse Params into a vector
  parseParams(&paramVec, LHSparamStr);

  // add params to parsed fact
  for(vector<string>::iterator it = paramVec.begin(); it != paramVec.end(); ++it){
   parsedRule += *it + "/";
  }

  // parse and add all predicates
  for(int i = RULE_FIRST_PRED_POS; i < ruleVec.size(); i++){
    parseAndAddRulePred(parsedRule, ruleVec[i]);
  }

  return parsedRule;
}

void parseAndAddRulePred(string &parsedRule, const string &Pred){

  // add PRED keyword separator
  parsedRule += "PRED/";
  
  // store Predicate Name
  size_t param_start_pos = Pred.find("(");
  size_t param_end_pos = Pred.find(")");
  size_t start = 0;
  size_t count = param_start_pos;
  parsedRule += Pred.substr(start,count) + "/";

  // add predicate params
  start = param_start_pos+1;
  count = param_end_pos-param_start_pos-1;
  string predParamStr = Pred.substr(start,count);

  // define parameter Vector
  vector<string> paramVec;

  // parse Params into a vector
  parseParams(&paramVec, predParamStr);

  // add params to parsed fact
  for(vector<string>::iterator it = paramVec.begin(); it != paramVec.end(); ++it){
   parsedRule += *it + "/";
  }


}

void parseParams(vector<string> *paramVec, const string &paramStr){
  
  // start from begining of string
  size_t current = 0;
  // get position of next delimeter ","
  size_t next = paramStr.find(",",current);

  // check if only one param
  if(next == string::npos && paramStr.length() > 0){
    paramVec->push_back(paramStr);
  }
  else{
    // loop until no more delimeters
    while(next!=string::npos){
      if(current == 0){
	paramVec->push_back(paramStr.substr(current, next-current));
      }
      else{
	paramVec->push_back(paramStr.substr(current+1, next-current-1));
      }
      current = next;
      next = paramStr.find(",",current+1);
    }
    
    // add last parameter to vector
    if(current>0){
      paramVec->push_back(paramStr.substr(current+1));
    }
  }
  
}

void writeToFile(const string &outputFileName,const string &outputText){
  // open output text file
  ofstream outfile(outputFileName,ofstream::out);

  // write FACTS and RULES
  outfile << outputText;

  // close Output file
  outfile.close();
}

/************* vecToString() ********************/
void vecToString(vector<string> &vec)
{
  for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it){
    cout<< *it << endl;
  }

}
