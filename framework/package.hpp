//
// Created by Hao Liu on 2021/9/25.
//

#pragma once
#include "types.hpp"

namespace canal
{
    class package
    {
    public:
        using element_type = uint8;
        using data_type = std::shared_ptr<element_type>;
        using size_type = int64;

        static constexpr size_type max_size() { return 65536L; }
        static constexpr size_type default_head_size() { return 48L; }

    public:
        package()
            : _data(new element_type[max_size()], std::default_delete<element_type[]>())
            , _begin_idx(default_head_size())
            , _end_idx(default_head_size() - 1)
        {
        }

        const element_type* data() const { return _data.get() + _begin_idx; }
        const size_type size() const { return _end_idx + 1 - _begin_idx; }

        // 跳过一部分空间，返回跳过的这部分空间的首地址
        element_type* skip_back(size_type len)
        {
            if (_end_idx + len >= max_size())
            {
                return nullptr;
            }
            element_type* result = _data.get() + _end_idx + 1;
            _end_idx += len;
            return result;
        }

        bool push_back(const element_type* data, size_type len)
        {
            if (_end_idx + len >= max_size())
            {
                return false;
            }
            std::memmove(_data.get() + _end_idx + 1, data, len);
            _end_idx += len;
            return true;
        }

        bool push_head(const element_type* data, size_type len)
        {
            if (_begin_idx - len < 0)
            {
                return false;
            }
            std::memmove(_data.get() + _begin_idx - len, data, len);
            _begin_idx -= len;
            return true;
        }

        bool pop_head(size_type len)
        {
            if (size() < len)
            {
                return false;
            }
            _begin_idx += len;
            return true;
        }

        bool push_head_uint(uint64 num)
        {
            element_type buffer[9] = {0};
            size_t use_size = 0;
            do
            {
                buffer[8 - use_size] = num & 0xff;
                num >>= 8;
                ++ use_size;
            } while (num > 0);
            element_type mask_check = ((1 << use_size) - 1) << (8 - use_size);
            if (buffer[9 - use_size] & mask_check)
            {
                ++ use_size;
            }
            element_type mask = use_size == 9 ? mask_check : ((1 << use_size) - 2) << (8 - use_size);
            buffer[9 - use_size] |= mask;
            return push_head(buffer + 9 - use_size, use_size);
        }

        std::optional<uint64> pop_head_uint()
        {
            if (size() < 1)
            {
                return std::optional<uint64>();
            }
            element_type first_element = *data();
            element_type temp = first_element;
            size_type use_size = 1;
            uint64 result = first_element;
            while (temp & 0x80)
            {
                ++ use_size;
                temp <<= 1;
                if (size() < use_size)
                {
                    return std::optional<uint64>();
                }
                result = (result << 8) + *(data() + use_size - 1);
            }
            assert(pop_head(use_size));
            if (use_size < 9)
            {
                result = result & ((static_cast<uint64>(1) << (use_size * 7 + 1)) - 1);
            }
            return result;
        }

        static void debug_test()
        {
            package test_package;
            uint64 test[18] = {
                0,
                0x7f,
                0x7f + 1,
                0x3fff,
                0x3fff + 1,
                0x1fffff,
                0x1fffff + 1,
                0xfffffff,
                0xfffffff + 1,
                0x7ffffffff,
                0x7ffffffff + 1,
                0x3ffffffffff,
                0x3ffffffffff + 1,
                0x1ffffffffffff,
                0x1ffffffffffff + 1,
                0xffffffffffffff,
                0xffffffffffffff + 1,
                0xffffffffffffffff
            };
            for (int i = 0; i < 18; ++ i)
            {
                uint64 test_num = test[i];
                assert(test_package.push_head_uint(test_num));
                auto num = test_package.pop_head_uint();
                assert(num);
                assert(*num == test_num);
            }
        }

    private:
        data_type       _data;
        size_type       _begin_idx;
        size_type       _end_idx;
    };
}
