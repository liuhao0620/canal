//
// Created by Hao Liu on 2021/10/2.
//

#pragma once
#include "chat_room.pb.h"
#include "logger.hpp"
#include "rpc_processer.hpp"

namespace chat_room
{
    class login_processer : public canal::rpc_processer
    {
    public:
        using login_response_return_type = std::function<void(const login_response&)>;

        virtual void process_request(const std::string& ep_name, canal::channel_id_type channel_id, const std::string& request_body, canal::rpc_return_type rpc_return) override
        {
            assert(rpc_return);
            login_request req;
            if (!req.ParseFromString(request_body))
            {
                // todo: return an error
                return;
            }
            process_request(ep_name, channel_id, req, [rpc_return](const login_response& response){
                rpc_return(response.SerializeAsString());
            });
        }

        void process_request(const std::string& ep_name, canal::channel_id_type channel_id, const login_request& request, login_response_return_type login_response_return)
        {
            canal::logger::log(
                "normal",
                canal::logger::level::debug,
                "receive login_request from %s[%ull]",
                ep_name.c_str(),
                channel_id
                );
            login_response_return(login_response());
        }

    };
}
