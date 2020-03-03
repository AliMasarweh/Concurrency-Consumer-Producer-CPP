//
// Created by ali-masa on 3/3/20.
//

#ifndef CONSUMER_PRODUCER_PRODUCER_H
#define CONSUMER_PRODUCER_PRODUCER_H

#include <sys/types.h>

class Store;

class Producer
{
public:
    Producer(Store* s, int id);
    void run();
    void* join();
    static int getNextProductAndIncerement();
    static int getNextProduct();

private:
    static void* addProductsToStore(void*);


    Store* m_store;
    pthread_t m_thread;
    int m_id;
    int m_product;
    static int s_product_num;
    const static int s_num_of_products = 120;
};


#endif //CONSUMER_PRODUCER_PRODUCER_H
