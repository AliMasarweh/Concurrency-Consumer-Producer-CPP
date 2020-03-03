//
// Created by ali-masa on 3/3/20.
//

#include <pthread.h>
#include "store.h"
#include "consumer.h"

#define PRODUCTS_NUM 40

Consumer::Consumer(Store *s, unsigned char id):m_store(s),m_thread(),m_id(id),m_product(-1){}

void Consumer::run()
{
    pthread_create(&m_thread, NULL, addProductsToStore, this);
}

void *Consumer::addProductsToStore(void * this_pntr)
{
    Consumer* _this = reinterpret_cast<Consumer*>(this_pntr);

    for (int i = 0; i < PRODUCTS_NUM; ++i)
    {
        _this->m_product = _this->m_store->consumeProduct();
    }

    return NULL;
}
