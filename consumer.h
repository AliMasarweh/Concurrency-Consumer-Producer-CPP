//
// Created by ali-masa on 3/3/20.
//

#ifndef CONSUMER_PRODUCER_CONSUMER_H
#define CONSUMER_PRODUCER_CONSUMER_H

#include <sys/types.h>
#include "store_user.h"
#include "../PlatformIndependentConcurrency/thread.h"

class Store;

class Consumer: public StoreUser
{
public:
    Consumer(Store& s);
    static bool decreaseProductsNum();
    ~Consumer();

private:
    static void* consumeProductsFromStore(void*);
    void* join();
    void run();

    static int s_product_quantity;
    static int s_counter;

    Thread* m_thread;
    int m_id;
    int m_product;
};


#endif //CONSUMER_PRODUCER_CONSUMER_H
