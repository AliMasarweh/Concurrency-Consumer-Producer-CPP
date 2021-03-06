//
// Created by ali-masa on 3/7/20.
//

#ifndef CONSUMER_PRODUCER_STORE_USER_H
#define CONSUMER_PRODUCER_STORE_USER_H

#include "mutex_store.h"

class StoreUser
{
public:
    StoreUser(Store& store):m_store(&store) {}
    virtual ~StoreUser() {};
    virtual void* join() = 0;
    virtual void run() = 0;

protected:
    Store* m_store;
};

#endif //CONSUMER_PRODUCER_STORE_USER_H
