//
// Created by ali-masa on 3/3/20.
//

#include <pthread.h>
#include <iostream>
#include "mutex_store.h"
#include "consumer.h"
#include "../PlatformIndependentConcurrency/linux_concurrency_abstract_factory.h"

#define PRODUCTS_NUM 30

using namespace std;

int Consumer::s_product_quantity = 120;
int Consumer::s_counter = 0;

Consumer::Consumer(Store& s):StoreUser(s),
m_thread(ConcurrencyAbstractFactory::getInstance()->createThread()),
m_id(++s_counter),m_product(-1){ this->run(); }

void Consumer::run()
{
    m_thread->run(consumeProductsFromStore, this);
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
    x = m_thread->join();
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

Consumer::~Consumer()
{
    this->join();
    delete m_thread;
}
