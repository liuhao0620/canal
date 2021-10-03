//
// Created by Hao Liu on 2021/10/2.
//
#include "chat_client.hpp"

int main(int argc, char** argv)
{
    std::shared_ptr<canal::thread_pool> app_thread_pool = std::make_shared<canal::thread_pool>(1);
    chat_room::chat_client app(app_thread_pool);
    app.run();
    canal::logger::log("normal", canal::logger::level::debug, "main");
    return 0;
}
