//
// Created by ali-masa on 3/3/20.
//

#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include "mutex_store.h"
#include "producer.h"
#include "consumer.h"

#define PRODUCING_NAME "mq_producing"
#define COSUMING_NAME "mq_consuming"

using namespace std;

MutexStore::MutexStore() : m_products_count(0)
{
    pthread_mutex_unlock(&m_producing_mutex);
    pthread_mutex_unlock(&m_consuming_mutex);
//    pthread_mutex_unlock(&m_items_mutex);
}

int MutexStore::addProduct(int product)
{
    pthread_mutex_lock(&m_producing_mutex);
    while(m_products_count == 6)
    {
        sleep(0.5);
        if(Producer::getNextProduct() >= 120)
        {
                pthread_mutex_unlock(&m_producing_mutex);
            return -1;
        }
    }
    m_products.push_back(Producer::getNextProductAndIncerement());
//    pthread_mutex_lock(&m_items_mutex);
    ++m_products_count;
//    pthread_mutex_unlock(&m_items_mutex);
    printf("produced product %d the count now is \%d\n",product, m_products_count);
    pthread_mutex_unlock(&m_producing_mutex);

    return product;
}

int MutexStore::consumeProduct()
{
    pthread_mutex_lock(&m_consuming_mutex);
    while(m_products_count == 0)
    {
        sleep(0.5);
        if(Consumer::getProductQuantity() <= 0)
        {
            pthread_mutex_unlock(&m_consuming_mutex);
            return -1;
        }
    }
//    pthread_mutex_lock(&m_items_mutex);
    int product = m_products[--m_products_count];
//    pthread_mutex_unlock(&m_items_mutex);
    Consumer::decreaseProductsNum();
    m_products.pop_back();
    printf("consumed product %d the count now is \%d\n",product, m_products_count);

    pthread_mutex_unlock(&m_consuming_mutex);

    return product;
}

MutexStore::~MutexStore() {}
