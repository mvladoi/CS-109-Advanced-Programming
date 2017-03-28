#include "Thread.h"
#include <vector>
#include "table.h"
#include "sri_engine.h"
#include "../fact/fact.h"
#include "../rule/rule.h"


class predicateThread: public Thread{
 private:

  // define predicate type
  int predicateType; // 0 means rule, 1 means fact

  // predicate pointer
  void* predPointer;
  
  // rule paramters vector
  vector<string> * ruleParams;

  // define master table pointer
  Table* masterTable;

  // define pointer to sri_engine
  SRIEngine* sri;
  
  // define masterTable mutex
  static pthread_mutex_t masterTable_mutex;  // A mutex that controls the execution of the thread

  // define print mutex
  static pthread_mutex_t print_mutex;  // A mutex that controls the execution of the thread

  // define predicate ID
  int predicateID;


 public:
  
  // define constructor
  predicateThread(int pred_t, void* predptr ,vector<string>* rParams, Table* masterT, SRIEngine* sri_ptr);
  
  // define a static method that creates a masterTable_mutex
  static void createStaticMutexes();
  
  // define thread main body
  virtual void* threadMainBody(void* arg);

  // define a static method that destroys a masterTable_mutex
  static void destroyStaticMutexes();

  // define a method that returns the predicate ID
  int getPredicateID();
  
  // define destructor
  ~predicateThread();


};
