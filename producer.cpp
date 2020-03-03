//
// Created by ali-masa on 3/3/20.
//

#include <pthread.h>
#include "producer.h"
#include "store.h"

#define PRODUCTS_NUM 40

Producer::Producer(Store *s, unsigned char id):m_store(s),m_thread(),m_id(id),m_product(id*PRODUCTS_NUM){}

void Producer::run()
{
    pthread_create(&m_thread, NULL, addProductsToStore, this);
}

void *Producer::addProductsToStore(void * this_pntr)
{
    Producer* _this = reinterpret_cast<Producer *>(this_pntr);
    unsigned char maxProduct = _this->m_product + PRODUCTS_NUM;

    for (int i = _this->m_product; i < maxProduct; ++i)
    {
        _this->m_store->addProduct(i);
    }

    return NULL;
}
