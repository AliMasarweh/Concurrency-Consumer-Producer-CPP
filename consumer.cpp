//
// Created by ali-masa on 3/3/20.
//

#include <pthread.h>
#include "store.h"
#include "consumer.h"

#define PRODUCTS_NUM 40

Consumer::Consumer(Store *s, unsigned char id):m_store(s),m_thread(),m_id(id),m_product(id*PRODUCTS_NUM){}

void Consumer::run()
{
    pthread_create(&m_thread, NULL, addProductsToStore, this);
}

void *Consumer::addProductsToStore(void * this_pntr)
{
    Consumer* _this = reinterpret_cast<Consumer*>(this_pntr);
    unsigned char maxProduct = _this->m_product + PRODUCTS_NUM;

    for (int i = _this->m_product; i < maxProduct; ++i)
    {
        _this->m_store->consumeProduct(i);
    }

    return NULL;
}
