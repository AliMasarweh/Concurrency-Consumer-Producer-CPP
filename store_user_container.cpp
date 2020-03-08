//
// Created by ali-masa on 3/7/20.
//

#include "store_user_container.h"
#include "producer.h"
#include "consumer.h"

void *StoreUsers::join()
{
    return 0;
}

void StoreUsers::run()
{

}

StoreUsers::StoreUsers(Store &s, int producers_num, int consumers_num) :StoreUser(s)
{
    for(int i = 0; i < producers_num;++i)
    {
        m_users.push_back(new Producer(s));
    }

    for(int i = producers_num; i < producers_num + consumers_num;++i)
    {
        m_users.push_back(new Consumer(s));
    }
}

StoreUsers::~StoreUsers()
{
    for (int i = m_users.size() - 1; i >= 0; --i)
    {
        delete (m_users[i]);
    }
}
