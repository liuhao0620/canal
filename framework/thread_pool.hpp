//
// Created by Hao Liu on 2021/10/1.
//

#pragma once
#include "boost/asio.hpp"

namespace canal
{
    class thread_pool
    {
    public:
        thread_pool(int thread_num) {}
        virtual ~thread_pool() {}

        virtual void add_work() {}
        virtual void run() {}
        virtual void close() {}
    };
}
