//
// Created by ali-masa on 3/3/20.
//

#ifndef CONSUMER_PRODUCER_CONSUMER_H
#define CONSUMER_PRODUCER_CONSUMER_H

#include <sys/types.h>

class Store;

class Consumer
{
public:
    Consumer(Store* s, int id);
    void run();
    void* join();

private:
    static void* consumeProductsFromStore(void*);

    Store* m_store;
    pthread_t m_thread;
    int m_id;
    int m_product;
};


#endif //CONSUMER_PRODUCER_CONSUMER_H
