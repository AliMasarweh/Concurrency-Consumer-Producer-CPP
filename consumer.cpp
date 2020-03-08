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
int Consumer::s_counter = 0;

Consumer::Consumer(Store *s):m_store(s),m_thread(),m_id(++s_counter),m_product(-1){ this->run(); }

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
