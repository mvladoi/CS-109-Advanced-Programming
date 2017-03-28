#include "andThread.h"

pthread_mutex_t andThread::printLock;

andThread::andThread(void *(*_threadRoutine) (void *), void *argument) : Thread(_threadRoutine) {
  args = argument;
  threadId = numThreads;
}

void *andThread::threadMainBody(void *arg) {
}

void andThread::createMutex() {
  pthread_mutex_init(&printLock,NULL);
}

void andThread::destroyMutex() {
  pthread_mutex_destroy(&printLock);
}

void andThread::start() {
  pthread_mutex_lock(&mutex); // Acquire lock before forking the thread
  started=true; // Set started to true
  // Invoke pthread create and pass to the routine the current object as the start routine need to be static
  int created = pthread_create (&pthread,&pthread_attr,andThread::run, (void *) this);
  if ( created != 0 ) // If the return in not zero then pthread_create failed
  {
    // Print an error message with the return integer value
    printf ("error creating thread: %d\n",created);
    // Check the error type and print an equivalent error message
    if (created == EAGAIN) printf ("EAGAIN generated\n");
    else if (created == EINVAL) printf ("EINVAL generated\n");
    else if (created == EPERM) printf ("EPERM generated\n");
    else if (created == ENOMEM) printf ("ENOMEM generated\n");
    started= false; // Set started to false
  }
  else setRunning(true); // Else thread is marked running 
}

void *andThread::run(void *input) {
  andThread *thread = (andThread *) input;
  pthread_mutex_lock(&printLock);
  std::cout << "AND Thread#" << thread->threadId << " started" << endl;
  pthread_mutex_unlock(&printLock);
  thread->threadRoutine(thread->args);
  thread->cleanup(thread);
  pthread_mutex_lock(&printLock);
  std::cout << "AND Thread#" << thread->threadId << " ended" << endl;
  pthread_mutex_unlock(&printLock);
  pthread_exit(NULL);
}
