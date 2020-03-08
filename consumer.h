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
    Consumer(Store* s);
    static bool decreaseProductsNum();
    static int getProductQuantity();
    ~Consumer() { this->join(); }

private:
    static void* consumeProductsFromStore(void*);
    void* join();
    void run();

    Store* m_store;
    pthread_t m_thread;
    static int s_counter;
    int m_id;
    int m_product;
    static int s_product_quantity;
    const static int s_num_of_products = 120;
};


#endif //CONSUMER_PRODUCER_CONSUMER_H
