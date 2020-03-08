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

    pthread_t m_thread;
    static int s_counter;
    int m_id;
    int m_product;
    static int s_product_num;
    const static int s_num_of_products = 120;
};


#endif //CONSUMER_PRODUCER_PRODUCER_H
