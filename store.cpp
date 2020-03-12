//
// Created by ali-masa on 3/11/20.
//

#include "store.h"
#include "producer.h"


Store::Store():m_products_count(0) {}

int Store::addProduct(int product)
{
    m_products.push_back(Producer::getNextProductAndIncrement());
    ++m_products_count;

    return 0;
}

int Store::consumeProduct()
{
    int product = m_products[--m_products_count];

    return product;
}
