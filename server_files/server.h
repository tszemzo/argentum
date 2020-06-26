
#ifndef _SERVER
#define _SERVER

#include <atomic>
#include <jsoncpp/json/json.h>

#include "../common_sockets.h"
#include "../common_sockets.h"
#include "../common_protocol_message.h"
#include "../common_queue.h"

class Server {
    std::atomic<bool> running;
    Socket skt;
    Json::Value config;
    // ProtocolTranslator protocol_translator;

    void initialize_config(const char* config_file);
    ProtocolMessage receive_msg(Socket skt);

    public:
        explicit Server(const char* config_file);

        void run();

        ~Server() {}
};



#endif
