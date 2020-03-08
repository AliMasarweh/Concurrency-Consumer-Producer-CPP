//
// Created by ali-masa on 3/3/20.
//

#ifndef CONSUMER_PRODUCER_PRODUCER_H
#define CONSUMER_PRODUCER_PRODUCER_H

#include <sys/types.h>
#include "store_user.h"

class Store;

class Producer: public StoreUser
{
public:
    Producer(Store& s);
    static int getNextProductAndIncerement();
    static int getNextProduct();
    ~Producer() { this->join(); }

private:
    static void* addProductsToStore(void*);
    void* join();
    void run();

    static int s_counter;
    static int s_product_num;
    const static int s_num_of_products = 120;

    pthread_t m_thread;
    int m_id;
    int m_product;
};


#endif //CONSUMER_PRODUCER_PRODUCER_H
