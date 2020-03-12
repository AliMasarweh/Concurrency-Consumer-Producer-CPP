//
// Created by ali-masa on 3/8/20.
//

#ifndef CONSUMER_PRODUCER_STORE_H
#define CONSUMER_PRODUCER_STORE_H

#include <vector>

class Store
{
public:
    Store();
    virtual int addProduct(int product);
    virtual int consumeProduct();
    /*virtual void lock(){};
    virtual void unlock(){};*/
    virtual ~Store() {};

protected:
    std::vector<int> m_products;
    int m_products_count;
};

#endif //CONSUMER_PRODUCER_STORE_H
