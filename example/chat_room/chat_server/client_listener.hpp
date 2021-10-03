//
// Created by Hao Liu on 2021/10/1.
//

#pragma once
#include "framework.hpp"
#include "chat_room.pb.h"
#include "chat_message_processer.hpp"
#include "login_processer.hpp"

namespace chat_room
{
    class client_listener : public canal::endpoint
    {
    public:
        virtual std::string get_name() const override
        {
            return "client_listener";
        }

        bool send(canal::channel_id_type channel_id, const chat_message& msg)
        {
            canal::package pack;
            canal::package::size_type len = msg.ByteSize();
            canal::package::element_type* data = pack.skip_back(len);
            if (data == nullptr)
            {
                return false;
            }
            if (!msg.SerializeToArray(data, len))
            {
                return false;
            }
            pack.push_head_uint(static_cast<canal::uint64>(mid_chat_message));
            return canal::endpoint::send(channel_id, pack);
        }

        bool send_response(canal::channel_id_type channel_id, canal::uint64 serial_number, const std::string& response_body)
        {
            canal_rpc_response rpc_res;
            rpc_res.set_serial_number(serial_number);
            rpc_res.set_response_body(response_body);
            canal::package pack;
            canal::package::size_type len = rpc_res.ByteSize();
            canal::package::element_type* data = pack.skip_back(len);
            if (data == nullptr)
            {
                return false;
            }
            if (!rpc_res.SerializeToArray(data, len))
            {
                return false;
            }
            pack.push_head_uint(static_cast<canal::uint64>(mid_canal_rpc_response));
            return canal::endpoint::send(channel_id, pack);
        }

        virtual void on_recv(canal::channel_id_type channel_id, canal::package pack) override
        {
            std::optional<canal::uint64> msg_id = pack.pop_head_uint();
            if (!msg_id)
            {
                // todo: error
                return;
            }
            switch (static_cast<message_id>(*msg_id))
            {
                case mid_canal_rpc_request:
                {
                    canal_rpc_request rpc_req;
                    if (!rpc_req.ParseFromArray(pack.data(), pack.size()))
                    {
                        // todo: error
                        return;
                    }
                    switch (rpc_req.request_message_id())
                    {
                        case mid_login_request:
                        {
                            login_processer login_proc;
                            canal::uint64 serial_number = rpc_req.serial_number();
                            login_proc.process_request(
                                get_name(),
                                channel_id,
                                rpc_req.request_body(),
                                [this, channel_id, serial_number](const std::string& response_body) {
                                    // todo: change this to weak_ptr
                                    send_response(channel_id, serial_number, response_body);
                                }
                                );
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    break;
                }
                case mid_chat_message:
                {
                    chat_message_processer proc;
                    proc.process(get_name(), channel_id, pack);
                    break;
                }
                default:
                {

                }
            }
        }
    };
}
