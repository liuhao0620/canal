//
// Created by Hao Liu on 2021/10/3.
//

#pragma once
#include "rpc_processer.hpp"
#include "chat_room.pb.h"

namespace chat_room
{
    class login_processer : public canal::rpc_processer
    {
    public:
        login_processer(const login_request& req)
            : _request(req)
        { }

        virtual void process_response(const std::string& ep_name, canal::channel_id_type channel_id, const std::string& response_body) override
        {

        }

        void process_response(const std::string& ep_name, canal::channel_id_type channel_id, const login_response& response)
        {

        }

        virtual void process_timeout(const std::string& ep, canal::channel_id_type channel_id) override
        {

        }

    private:
        login_request _request;
    };
}
