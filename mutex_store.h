//
// Created by ali-masa on 3/3/20.
//

#ifndef CONSUMER_PRODUCER_MUTEX_STORE_H
#define CONSUMER_PRODUCER_MUTEX_STORE_H


#include <sys/types.h>
#include <vector>
#include <mqueue.h>
#include "store.h"

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
    pthread_mutex_t m_producing_mutex;
    pthread_mutex_t m_consuming_mutex;

//    pthread_mutex_t m_items_mutex;

    /*mq_attr m_producing_attr;
    mq_attr m_consuming_attr;
    mqd_t m_producing_mq;
    mqd_t m_consuming_mq;*/
};


#endif //CONSUMER_PRODUCER_MUTEX_STORE_H
