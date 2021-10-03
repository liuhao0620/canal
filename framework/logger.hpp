//
// Created by Hao Liu on 2021/10/1.
//

#pragma once

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>

namespace canal
{
    class logger
    {
    public:
        enum class level : uint8
        {
            all,
            verbose = all,
            debug,
            info,
            warning,
            error,
            fatal,
            off,
            num = off
        };

    public:
        static void log(const std::string& category, level lv, const char* msg)
        {
            get_instance().log_impl(category, lv, msg);
        }
        template <class... ARGS>
        static void log(const std::string& category, level lv, const char* fmt, ARGS&& ...args)
        {
            char logBuffer[1024] = {0};
            snprintf(logBuffer, 1023, fmt, std::forward<ARGS>(args)...);
            get_instance().log_impl(category, lv, logBuffer);
        }

    protected:
        static logger& get_instance()
        {
            static logger logger_instance;
            return logger_instance;
        }
        static const std::string get_time_string()
        {
            auto tNow = std::chrono::system_clock::now();
            auto tmNow = std::chrono::system_clock::to_time_t(tNow);
            auto tSeconds = std::chrono::duration_cast<std::chrono::seconds>(tNow.time_since_epoch());
            auto tMilli = std::chrono::duration_cast<std::chrono::milliseconds>(tNow.time_since_epoch());
            auto ms = tMilli - tSeconds;

            std::ostringstream os;
            os << std::put_time(std::localtime(&tmNow), "%Y-%m-%d %H:%M:%S.") << std::setfill('0') << std::setw(3) << ms.count();
            return os.str();
        }
        virtual void log_impl(const std::string& category, level lv, const char* fmt)
        {
            std::cout << category << " [" << static_cast<int32>(lv) << "] " << fmt << std::endl;
        }
    };
}
