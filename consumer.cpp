//
// Created by ali-masa on 3/3/20.
//

#include <pthread.h>
#include <iostream>
#include "store.h"
#include "consumer.h"

#define PRODUCTS_NUM 30

using namespace std;

int Consumer::s_product_quantity = 120;

Consumer::Consumer(Store *s, int id):m_store(s),m_thread(),m_id(id),m_product(-1){}

void Consumer::run()
{
    pthread_create(&m_thread, NULL, consumeProductsFromStore, this);
}

void *Consumer::consumeProductsFromStore(void * this_pntr)
{
    Consumer* _this = reinterpret_cast<Consumer*>(this_pntr);

    while(Consumer::s_product_quantity > 0)
    {
        _this->m_product = _this->m_store->consumeProduct();
    }

    return NULL;
}

void *Consumer::join()
{
    void* x;
    pthread_join(m_thread, &x);

    return x;
}

bool Consumer::decreaseProductsNum()
{
    if(s_product_quantity <= 0)
        return false;

    --s_product_quantity;
    return true;
}

int Consumer::getProductQuantity()
{
    return s_product_quantity;
}
