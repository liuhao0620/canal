//
// Created by Hao Liu on 2021/10/1.
//

#include "chat_server.hpp"
#include "thread_pool.hpp"

int main(int argc, char** argv)
{
    std::shared_ptr<canal::thread_pool> app_thread_pool = std::make_shared<canal::thread_pool>(1);
    chat_room::chat_server app(app_thread_pool);
    app.run();
    canal::logger::log("normal", canal::logger::level::debug, "main");
    return 0;
}

