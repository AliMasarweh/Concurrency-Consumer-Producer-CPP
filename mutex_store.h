//
// Created by ali-masa on 3/3/20.
//

#ifndef CONSUMER_PRODUCER_MUTEX_STORE_H
#define CONSUMER_PRODUCER_MUTEX_STORE_H


#include <sys/types.h>
#include <vector>
#include <mqueue.h>
#include "store.h"
#include "PlatformIndependentConcurrency/mutex.h"

class MutexStore : public Store
{
public:
    MutexStore();
    int addProduct(int product);
    int consumeProduct();
    ~MutexStore();

private:
    std::vector<int> m_products;
    int m_products_count;
    Mutex* m_producing_mutex;
    Mutex* m_consuming_mutex;
};


#endif //CONSUMER_PRODUCER_MUTEX_STORE_H
