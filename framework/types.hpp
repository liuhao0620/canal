//
// Created by Hao Liu on 2021/9/25.
//

#pragma once
#include <functional>
#include <memory>
#include <optional>
#include <string>

namespace canal
{
    using int8 = char;
    using uint8 = unsigned char;
    using int16 = short;
    using uint16 = unsigned short;
    using int32 = int;
    using uint32 = unsigned int;
    using int64 = long long;
    using uint64 = unsigned long long;

    using channel_id_type = uint64;

    static_assert(sizeof(int8) == 1);
    static_assert(sizeof(uint8) == 1);
    static_assert(sizeof(int16) == 2);
    static_assert(sizeof(uint16) == 2);
    static_assert(sizeof(int32) == 4);
    static_assert(sizeof(uint32) == 4);
    static_assert(sizeof(int64) == 8);
    static_assert(sizeof(uint64) == 8);
}
