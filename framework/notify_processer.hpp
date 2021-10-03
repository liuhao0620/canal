//
// Created by Hao Liu on 2021/10/1.
//

#pragma once
#include "package.hpp"
#include "endpoint.hpp"

namespace canal
{
    class notify_processer
    {
    public:
        virtual void process(std::string ep_name, channel_id_type channel_id, package pack) = 0;
    };
}
