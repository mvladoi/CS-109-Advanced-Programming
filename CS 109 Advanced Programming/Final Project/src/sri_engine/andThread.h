#ifndef AND_THREAD_H
#define AND_THREAD_H
#include "Thread.h"

class andThread : public Thread {
  private:
    void *args;
    int threadId;
    static pthread_mutex_t printLock;
  public:
    andThread(void *(*_threadRoutine) (void *) = NULL, void *args = NULL);
    bool isStarting();
    void *threadMainBody(void *arg);
    void start();
    static void createMutex();
    static void destroyMutex();
    static void *run(void *input);
};
#endif
