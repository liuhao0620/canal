//
// Created by Hao Liu on 2021/10/2.
//

#pragma once
#include "types.hpp"

namespace canal
{
    using rpc_return_type = std::function<void(const std::string&)>;
    class rpc_processer
    {
    public:
        virtual void process_request(const std::string& ep_name, channel_id_type channel_id, const std::string& request_body, rpc_return_type rpc_return)
        {
            assert(false);
        }

        virtual void process_response(const std::string& ep_name, channel_id_type channel_id, const std::string& response_body)
        {
            assert(false);
        }

        virtual void process_timeout(const std::string& ep, channel_id_type channel_id)
        {
            assert(false);
        }
    };
}
