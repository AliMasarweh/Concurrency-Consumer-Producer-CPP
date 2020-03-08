//
// Created by ali-masa on 3/8/20.
//

#ifndef CONSUMER_PRODUCER_MESSAGE_QUEUE_STORE_H
#define CONSUMER_PRODUCER_MESSAGE_QUEUE_STORE_H

#include "PlatformIndependentConcurrency/message_queue.h"

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

    MessageQueue* m_producing_mq;
    MessageQueue* m_consuming_mq;
};

#endif //CONSUMER_PRODUCER_MESSAGE_QUEUE_STORE_H
