#ifndef THREADMANAGER_H
#define THREADMANAGER_H
#include "common.h"
#include "Thread.h"
// A thread manager class that managed a group of threads
class ThreadManager
{
 private:
  vector <Thread *> threads; // Vector of Thread pointers
 public:
  ThreadManager(); // Constructor
  void addThread (Thread * p_thread); // Add a thread
  void start(); // Start all threads
  void barrier(); // Wait for all threads to finish
  ~ThreadManager(); // Destructor
};
#endif
