//
// Created by ali-masa on 3/3/20.
//
#include <cstddef>
#include "producer.h"
#include "mutex_store.h"
#include "../PlatformIndependentConcurrency/linux_concurrency_abstract_factory.h"

using namespace std;

int Producer::s_product_num = 0;
int Producer::s_counter = 0;

Producer::Producer(Store& s):StoreUser(s),
m_thread(ConcurrencyAbstractFactory::getInstance()->createThread())
,m_id(++s_counter){ this->run(); }

void Producer::run()
{
    m_thread->run(addProductsToStore, this);
}

void *Producer::addProductsToStore(void * this_pntr)
{
    Producer* _this = reinterpret_cast<Producer*>(this_pntr);
    int i = -1;
    while (Producer::canProduceProducts())
    {
        _this->m_store->addProduct(i);
    }

    return NULL;
}

void* Producer::join()
{
    return m_thread->join();
}

int Producer::getNextProduct()
{
    return s_product_num;
}

int Producer::getNextProductAndIncrement()
{
    return ++s_product_num;
}

Producer::~Producer()
{
    this->join();
    delete m_thread;
}

bool Producer::canProduceProducts()
{
    return s_product_num < s_stock_of_products;
}
