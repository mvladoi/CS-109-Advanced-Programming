#include "predicateThread.h"
#include <iostream>

pthread_mutex_t predicateThread::masterTable_mutex;
pthread_mutex_t predicateThread::print_mutex;

// define constructor
predicateThread::predicateThread(int pred_t, void* predptr ,vector<string>* rParams, Table* masterT, SRIEngine* sri_ptr){
  predicateType = pred_t;
  predPointer = predptr;
  ruleParams = rParams;
  masterTable = masterT;
  sri = sri_ptr;
  predicateID = numThreads;
}

// define threadMainBody
void* predicateThread::threadMainBody(void *arg){

  // Lock print mutex
  pthread_mutex_lock(&print_mutex);
  // print statement that indicates start of thread
  std::cout<<"OR  Thread#"<<predicateID<<" started"<<"\n";
  // Unlock print mutex
  pthread_mutex_unlock(&print_mutex);
  
  if (predicateType == 0) {
    Fact* workfact = (Fact*) predPointer;
    Table *T = sri->expandFact(workfact, *ruleParams);
    pthread_mutex_lock(&masterTable_mutex); // Lock mutex which will block in case the thread is running
    masterTable->cat(*T);
    pthread_mutex_unlock(&masterTable_mutex);   // Unlock mutex as soon as it is acquired,which guarantees that the thread terminated
    //std::cout<<"Thread#"<<(long)pthread_self()<<":\n";
    //std::cout<<"Executing Fact: "<< workfact->toString()<<"\n";
  }
  else{
    Rule* workrule = (Rule*) predPointer;
    Table *T = sri->expandRule(workrule, *ruleParams);
    pthread_mutex_lock(&masterTable_mutex); // Lock mutex which will block in case the thread is running
    masterTable->cat(*T);
    pthread_mutex_unlock(&masterTable_mutex);   // Unlock mutex as soon as it is
    //std::cout<<"Thread#"<<(long)pthread_self()<<":\n";
    //std::cout<<"Executing Rule: "<< workrule->toString()<<"\n";
  }
  
  // Lock print mutex
  pthread_mutex_lock(&print_mutex);
  // print statement that indicates start of thread
  std::cout<<"OR  Thread#"<<predicateID<<" ended"<<"\n";
  // Unlock print mutex
  pthread_mutex_unlock(&print_mutex);
}

// define a static method that creates a masterTable_mutex
void predicateThread::createStaticMutexes(){
  // initialize number of threads
  pthread_mutex_init(&masterTable_mutex,NULL);// Initialize execution control mutex
  pthread_mutex_init(&print_mutex,NULL);// Initialize print mutex
}

// define a static method that destroys a masterTable_mutex
void predicateThread::destroyStaticMutexes(){
  pthread_mutex_destroy(&masterTable_mutex);  //Destroy execution control mutex
  pthread_mutex_destroy(&print_mutex);// Destroy print mutex
}

// define a method that returns the predicate ID
int predicateThread::getPredicateID(){
  return predicateID;
}

// define destructor
predicateThread::~predicateThread(){}
