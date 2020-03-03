//
// Created by ali-masa on 3/3/20.
//

#include <pthread.h>
#include <iostream>
#include "producer.h"
#include "store.h"

#define PRODUCTS_NUM 40

using namespace std;

int Producer::s_product_num = 1;

Producer::Producer(Store *s, int id):m_store(s),m_thread(),m_id(id),m_product(id*PRODUCTS_NUM){}

void Producer::run()
{
    pthread_create(&m_thread, NULL, addProductsToStore, this);
}

void *Producer::addProductsToStore(void * this_pntr)
{
    Producer* _this = reinterpret_cast<Producer*>(this_pntr);
    unsigned char maxProduct = _this->m_product + PRODUCTS_NUM;
    int i = -1;
    while ((i = getNextProduct()) < s_num_of_products)
    {
        _this->m_store->addProduct(i);
    }

    return NULL;
}

void* Producer::join()
{
    void* x;
    pthread_join(m_thread, &x);

    return x;
}

int Producer::getNextProduct()
{
    return s_product_num;
}

int Producer::getNextProductAndIncerement()
{
    return s_product_num++;
}
