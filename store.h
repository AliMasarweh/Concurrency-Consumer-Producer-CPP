//
// Created by ali-masa on 3/3/20.
//

#ifndef CONSUMER_PRODUCER_STORE_H
#define CONSUMER_PRODUCER_STORE_H


#include <sys/types.h>

class Store
{
public:
    Store();
    unsigned char addProduct(unsigned char product);
    unsigned char consumeProduct(unsigned char product);

private:
    unsigned char m_products[6];
    unsigned char m_products_count;
    pthread_mutex_t m_producing_mutex;
    pthread_mutex_t m_consuming_mutex;
};


#endif //CONSUMER_PRODUCER_STORE_H
