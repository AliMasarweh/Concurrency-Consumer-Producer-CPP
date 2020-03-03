//
// Created by ali-masa on 3/3/20.
//

#include <pthread.h>
#include "store.h"

Store::Store() : m_products_count(0) {}

unsigned char Store::addProduct(unsigned char product)
{
    pthread_mutex_lock(&m_producing_mutex);
    while(m_products_count < 6);
    m_products[m_products_count++] = product;
    pthread_mutex_lock(&m_producing_mutex);

    return product;
}

unsigned char Store::consumeProduct()
{
    pthread_mutex_lock(&m_consuming_mutex);
    while(m_products_count > 0);
    unsigned char product = m_products[m_products_count--];
    pthread_mutex_lock(&m_consuming_mutex);

    return product;
}
