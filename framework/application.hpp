//
// Created by Hao Liu on 2021/9/25.
//

#pragma once
#include "types.hpp"
#include "thread_pool.hpp"

namespace canal
{
    class application
    {
    public:
        application(std::shared_ptr<thread_pool> app_thread_pool)
            : _thread_pool(app_thread_pool)
        { }
        virtual ~application()
        { }
        virtual void run()
        {
            _thread_pool->run();
        }
        virtual void close()
        {
            _thread_pool->close();
        }

    protected:
        std::shared_ptr<thread_pool>    _thread_pool;
    };
}
