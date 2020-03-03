//
// Created by ali-masa on 3/3/20.
//

#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <cstdio>
#include "store.h"
#include "producer.h"
#include "consumer.h"

using namespace std;

Store::Store() : m_products_count(0)
{
    pthread_mutex_unlock(&m_producing_mutex);
    pthread_mutex_unlock(&m_consuming_mutex);
}

int Store::addProduct(int product)
{
    pthread_mutex_lock(&m_producing_mutex);
    while(m_products_count == 6)
    {
        sleep(0.5);
    }
    m_products.push_back(Producer::getNextProductAndIncerement());
    ++m_products_count;
    printf("produced product %d the count now is \%d\n",product, m_products_count);
    pthread_mutex_unlock(&m_producing_mutex);

    return product;
}

int Store::consumeProduct()
{
    pthread_mutex_lock(&m_consuming_mutex);
    while(m_products_count == 0)
    {
        sleep(0.5);
    }
    int product = m_products[--m_products_count];
    Consumer::decreaseProductsNum();
    m_products.pop_back();
    printf("consumed product %d the count now is \%d\n",product, m_products_count);
    pthread_mutex_unlock(&m_consuming_mutex);

    return product;
}
