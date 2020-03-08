//
// Created by ali-masa on 3/8/20.
//

#ifndef CONSUMER_PRODUCER_STORE_H
#define CONSUMER_PRODUCER_STORE_H

class Store
{
public:
    virtual int addProduct(int product) = 0;
    virtual int consumeProduct() = 0;
    virtual ~Store() {};
};

#endif //CONSUMER_PRODUCER_STORE_H
