//
// Created by ali-masa on 3/3/20.
//

#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <cstdio>
#include "mutex_store.h"
#include "producer.h"
#include "consumer.h"
#include "PlatformIndependentConcurrency/linux_mutex.h"

using namespace std;

MutexStore::MutexStore() : m_products_count(0), m_consuming_mutex(new LinuxMutex()),
m_producing_mutex(new LinuxMutex()), m_items_mutex(new LinuxMutex())
{
    m_producing_mutex->unlock();
    m_consuming_mutex->unlock();
    m_items_mutex->unlock();
}

int MutexStore::addProduct(int product)
{
    m_producing_mutex->lock();
    while(m_products_count == 6)
    {
        sleep(0.5);
        if(Producer::getNextProduct() >= 120)
        {
            m_producing_mutex->unlock();
            return -1;
        }
    }
    m_products.push_back(Producer::getNextProductAndIncerement());
    m_items_mutex->lock();
    ++m_products_count;
    m_items_mutex->unlock();
    printf("produced product %d the count now is \%d\n",product, m_products_count);
    m_producing_mutex->unlock();

    return product;
}

int MutexStore::consumeProduct()
{
    m_consuming_mutex->lock();
    while(m_products_count == 0)
    {
        sleep(0.5);
        if(Consumer::getProductQuantity() <= 0)
        {
            m_consuming_mutex->unlock();
            return -1;
        }
    }
    m_items_mutex->lock();
    --m_products_count;
    m_items_mutex->unlock();
    int product = m_products[m_products_count];
    Consumer::decreaseProductsNum();
    m_products.pop_back();
    printf("consumed product %d the count now is \%d\n",product, m_products_count);

    m_consuming_mutex->unlock();

    return product;
}

MutexStore::~MutexStore()
{
    delete m_consuming_mutex;
    delete m_producing_mutex;
}
