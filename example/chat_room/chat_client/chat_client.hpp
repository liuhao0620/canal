//
// Created by Hao Liu on 2021/10/2.
//

#pragma once
#include "application.hpp"
#include "server_connector.hpp"

namespace chat_room
{
    class chat_client : public canal::application
    {
    public:
        chat_client(std::shared_ptr<canal::thread_pool> chat_client_thread_pool)
            : canal::application(chat_client_thread_pool)
        { }

    private:
        std::unique_ptr<server_connector>       _server_connector;
    };
}
