//
// Created by Hao Liu on 2021/10/1.
//

#pragma once
#include "notify_processer.hpp"
#include "chat_room.pb.h"
#include "logger.hpp"

namespace chat_room
{
    class chat_message_processer : public canal::notify_processer
    {
    public:
        virtual void process(std::string ep_name, canal::channel_id_type channel_id, canal::package pack) override
        {
            chat_message msg;
            if (msg.ParseFromArray(pack.data(), pack.size()))
            {
                process(ep_name, channel_id, msg);
            }
        }

        void process(std::string ep_name, canal::channel_id_type channel_id, const chat_message& msg)
        {
            canal::logger::log(
                "normal",
                canal::logger::level::debug,
                "receive chat_message from %s[%ull]",
                ep_name.c_str(),
                channel_id
                );
        }
    };
}
