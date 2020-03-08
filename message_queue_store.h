//
// Created by ali-masa on 3/8/20.
//

#ifndef CONSUMER_PRODUCER_MESSAGE_QUEUE_STORE_H
#define CONSUMER_PRODUCER_MESSAGE_QUEUE_STORE_H



#include <sys/types.h>
#include <vector>
#include <mqueue.h>
#include "store.h"

#define PMODE 0700

class MQueueStore : public Store
{
public:
    MQueueStore();
    int addProduct(int product);
    int consumeProduct();
    ~MQueueStore();

private:
    std::vector<int> m_products;
    int m_products_count;

    mq_attr m_producing_attr;
    mq_attr m_consuming_attr;
    mqd_t m_producing_mq;
    mqd_t m_consuming_mq;
};

#endif //CONSUMER_PRODUCER_MESSAGE_QUEUE_STORE_H