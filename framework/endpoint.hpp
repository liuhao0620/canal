//
// Created by Hao Liu on 2021/9/25.
//

#pragma once
#include "types.hpp"
#include "package.hpp"

namespace canal
{
    class endpoint
    {
    public:
        virtual bool send(channel_id_type channel_id, package pack) { return true; }
        virtual void on_recv(channel_id_type channel_id, package pack) { }
        virtual std::string get_name() const = 0;
    };
}
