//
// Created by ali-masa on 3/7/20.
//

#ifndef CONSUMER_PRODUCER_STORE_USER_CONTAINER_H
#define CONSUMER_PRODUCER_STORE_USER_CONTAINER_H


#include "store_user.h"

class StoreUsers : public StoreUser
{
public:
    StoreUsers(MutexStore& s, int producers_num, int consumers_num);
    ~StoreUsers();
private:
    virtual void *join();
    virtual void run();

    std::vector<StoreUser*> m_users;
};


#endif //CONSUMER_PRODUCER_STORE_USER_CONTAINER_H
