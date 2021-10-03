//
// Created by Hao Liu on 2021/10/1.
//

#pragma once
#include "framework.hpp"
#include "client_listener.hpp"

namespace chat_room
{
    class chat_server : public canal::application
    {
    public:
        chat_server(std::shared_ptr<canal::thread_pool> chat_server_thread_pool)
            : canal::application(chat_server_thread_pool)
        {
        }

    private:
        std::unique_ptr<client_listener>        _client_listener;
    };
}
