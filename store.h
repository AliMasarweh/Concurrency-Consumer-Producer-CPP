//
// Created by ali-masa on 3/3/20.
//

#ifndef CONSUMER_PRODUCER_STORE_H
#define CONSUMER_PRODUCER_STORE_H


#include <sys/types.h>
#include <vector>

class Store
{
public:
    Store();
    int addProduct(int product);
    int consumeProduct();

private:
    std::vector<int> m_products;
    int m_products_count;
    pthread_mutex_t m_producing_mutex;
    pthread_mutex_t m_consuming_mutex;
//    pthread_mutex_t m_items_mutex;
};


#endif //CONSUMER_PRODUCER_STORE_H
