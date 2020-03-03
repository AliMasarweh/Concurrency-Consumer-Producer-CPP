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
    Consumer(Store* s, unsigned char id);
    void run();

private:
    static void* addProductsToStore(void*);

    Store* m_store;
    pthread_t m_thread;
    unsigned char m_id;
    unsigned char m_product;
};


#endif //CONSUMER_PRODUCER_CONSUMER_H