//
// Created by ali-masa on 3/8/20.
//
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include "producer.h"
#include "message_queue_store.h"
#include "consumer.h"

#define PRODUCING_NAME "mq_producing"
#define CONSUMING_NAME "mq_consuming"

MQueueStore::MQueueStore() : m_products_count(0)
{
    m_producing_attr.mq_maxmsg = 6;
    m_producing_attr.mq_msgsize = 20;
    m_producing_mq = mq_open(PRODUCING_NAME,  O_RDWR|O_CREAT, PMODE, &m_producing_attr);

    m_consuming_attr.mq_maxmsg = 6;
    m_consuming_attr.mq_msgsize = 20;
    m_consuming_mq = mq_open(CONSUMING_NAME,  O_RDWR|O_CREAT, PMODE, &m_consuming_attr);

    for (int i = 0; i < m_producing_attr.mq_maxmsg; ++i)
    {
        mq_send(m_producing_mq, "Produce", strlen("Produce")+1 ,0);
    }
}

int MQueueStore::addProduct(int product)
{
    char buff[20];
    int status = mq_receive(m_producing_mq, buff, 20, 0);
    if(status == -1)
    {
        printf("producing status is -1\n");
    }
    while(m_products_count == 6)
    {
        sleep(0.5);
        if(Producer::getNextProduct() >= 120)
        {
            mq_send(m_producing_mq, "Producing is empty", strlen("Producing is empty") + 1, 0);
            return -1;
        }
    }
    m_products.push_back(Producer::getNextProductAndIncerement());
    ++m_products_count;
    printf("produced product %d the count now is \%d\n",product, m_products_count);
    mq_send(m_producing_mq, "Produce", strlen("Produce")+1, 0);

    return product;
}


int MQueueStore::consumeProduct()
{
    char buff[20];
    int status = mq_receive(m_consuming_mq, buff, 20, 0);
    if(status == -1)
    {
        printf("consuming status is -1\n");
    }
    while(m_products_count == 0)
    {
        sleep(0.5);
        if(Consumer::getProductQuantity() <= 0)
        {
            mq_send(m_consuming_mq, "Consuming is empty", strlen("Consuming is empty")+1, 0);
            return -1;
        }
    }
    int product = m_products[--m_products_count];
    Consumer::decreaseProductsNum();
    m_products.pop_back();
    printf("consumed product %d the count now is \%d\n",product, m_products_count);
    mq_send(m_consuming_mq, "Consume", strlen("Consume") + 1, 0);

    return product;
}


MQueueStore::~MQueueStore()
{
    mq_unlink(PRODUCING_NAME);
    mq_unlink(CONSUMING_NAME);
    mq_close(m_producing_mq);
    mq_close(m_consuming_mq);
}