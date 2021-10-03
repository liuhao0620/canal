//
// Created by Hao Liu on 2021/10/2.
//

#pragma once
#include "endpoint.hpp"
#include "chat_room.pb.h"
#include "login_processer.hpp"
#include "chat_message_processer.hpp"
#include "package.hpp"

namespace chat_room
{
    class server_connector : public canal::endpoint
    {
    public:
        virtual std::string get_name() const override
        {
            return "server_connector";
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

        bool rpc_send(canal::channel_id_type channel_id, const login_request& req)
        {
            canal_rpc_request rpc_req;
            canal::uint64 serial_number = get_rpc_serial_number();
            rpc_req.set_serial_number(serial_number);
            rpc_req.set_request_message_id(mid_login_request);
            rpc_req.set_request_body(req.SerializeAsString());
            canal::package pack;
            canal::package::size_type len = rpc_req.ByteSize();
            canal::package::element_type* data = pack.skip_back(len);
            if (data == nullptr)
            {
                return false;
            }
            if (!rpc_req.SerializeToArray(data, len))
            {
                return false;
            }
            pack.push_head_uint(static_cast<canal::uint64>(mid_canal_rpc_request));
            if(!canal::endpoint::send(channel_id, pack))
            {
                return false;
            }
            std::shared_ptr<canal::rpc_processer> login_proc(new login_processer(req));
            _rpc_processers.insert(std::make_pair(serial_number, login_proc));
            return true;
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
                case mid_canal_rpc_response:
                {
                    canal_rpc_response rpc_res;
                    if (!rpc_res.ParseFromArray(pack.data(), pack.size()))
                    {
                        // todo: error
                        return;
                    }
                    auto iter = _rpc_processers.find(rpc_res.serial_number());
                    if (iter == _rpc_processers.end())
                    {
                        // todo: error
                        return;
                    }
                    std::shared_ptr<canal::rpc_processer> rpc_proc = iter->second;
                    _rpc_processers.erase(iter);
                    rpc_proc->process_response(get_name(), channel_id, rpc_res.response_body());
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
                    break;
                }
            }
        }

    protected:
        static canal::uint64 get_rpc_serial_number()
        {
            static canal::uint64 serial_number_index = 0;
            return ++ serial_number_index;
        }

        std::unordered_map<canal::uint64, std::shared_ptr<canal::rpc_processer>>    _rpc_processers;
    };
}
