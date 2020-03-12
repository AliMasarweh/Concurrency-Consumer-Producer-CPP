//
// Created by ali-masa on 3/8/20.
//
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include "producer.h"
#include "message_queue_store.h"
#include "consumer.h"
#include "../PlatformIndependentConcurrency/linux_concurrency_abstract_factory.h"

#define PRODUCING_NAME "mq_producing"
#define CONSUMING_NAME "mq_consuming"
#define MUTEXING_ITEMS_NAME "mq_items"

MQueueStore::MQueueStore() : m_products_count(0)
{
    m_producing_mq = ConcurrencyAbstractFactory::getInstance()->createMessageQueue();
    m_consuming_mq = ConcurrencyAbstractFactory::getInstance()->createMessageQueue();
    m_items_mq = ConcurrencyAbstractFactory::getInstance()->createMessageQueue();

    m_producing_mq->open(PRODUCING_NAME, O_RDWR|O_CREAT, PMODE,
                         6 , 20);
    m_consuming_mq->open(CONSUMING_NAME,  O_RDWR|O_CREAT, PMODE,
                         6 , 20);
    m_items_mq->open(MUTEXING_ITEMS_NAME, O_RDWR|O_CREAT, PMODE,
                     1 , 20);

    m_items_mq->send("Can manipulate", strlen("Can manipulate")+1,0);

    for (int i = 0; i < 6; ++i)
    {
        m_producing_mq->send("Produce", strlen("Produce")+1 ,0);
    }
}

int MQueueStore::addProduct(int product)
{
    char buff[20];
    int status = m_producing_mq->receive(buff, 20, 0);
    if(status == -1)
    {
        printf("producing status is -1\n");
    }
    while(m_products_count == 6)
    {
        sleep(0.5);
        if(!Producer::canProduceProducts())
        {
            m_producing_mq->send("Producing is empty", strlen("Producing is empty") + 1, 0);
            return -1;
        }
    }
    m_items_mq->receive(buff, 20,0);
    m_products.push_back(Producer::getNextProductAndIncrement());
    ++m_products_count;
    m_items_mq->send("Can manipulate", strlen("Can manipulate")+1,0);
    printf("produced product %d the count now is \%d\n",product, m_products_count);
    m_producing_mq->send("Produce", strlen("Produce")+1, 0);

    return product;
}


int MQueueStore::consumeProduct()
{
    char buff[20];
    int status = m_consuming_mq->receive(buff, 20, 0);
    if(status == -1)
    {
        printf("consuming status is -1\n");
    }
    while(m_products_count == 0)
    {
        sleep(0.5);
        if(!Producer::canProduceProducts())
        {
            m_consuming_mq->send("Consuming is empty", strlen("Consuming is empty")+1, 0);
            return -1;
        }
    }
    m_items_mq->receive(buff, 20,0);
    int product = m_products[--m_products_count];
    Consumer::decreaseProductsNum();
    m_products.pop_back();
    m_items_mq->send("Can manipulate", strlen("Can manipulate")+1,0);
    printf("consumed product %d the count now is \%d\n",product, m_products_count);
    m_consuming_mq->send("Consume", strlen("Consume") + 1, 0);

    return product;
}


MQueueStore::~MQueueStore()
{
    delete m_items_mq;
    delete m_producing_mq;
    delete m_consuming_mq;
}