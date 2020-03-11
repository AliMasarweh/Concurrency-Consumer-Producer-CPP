//
// Created by ali-masa on 3/3/20.
//

#ifndef CONSUMER_PRODUCER_PRODUCER_H
#define CONSUMER_PRODUCER_PRODUCER_H

#include "store_user.h"
#include "../PlatformIndependentConcurrency/thread.h"

class Store;

class Producer: public StoreUser
{
public:
    Producer(Store& s);
    // Increment
    static int getNextProductAndIncrement();
    static int getNextProduct();
    ~Producer();

private:
    static void* addProductsToStore(void*);
    void* join();
    void run();

    static int s_counter;
    static int s_product_num;
    const static int s_num_of_products = 119;

    Thread* m_thread;
    int m_id;
};


#endif //CONSUMER_PRODUCER_PRODUCER_H
