#include <iostream>
#include <semaphore.h>

class Sem
{
public:
    Sem(int value) {
        sem_init(&m_sem, 0, value);
    }
    ~Sem() {
        sem_destroy(&m_sem);
    }
    void p() {
        sem_wait(&m_sem);       
    }
    void v() {
        sem_post(&m_sem);
    }
private:
    sem_t m_sem;
};