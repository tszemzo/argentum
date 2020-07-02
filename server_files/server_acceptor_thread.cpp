
#include "server_acceptor_thread.h"
#include "server_processor_thread.h"

#include "../common_mapinfo.h"
#include "../common_sockets.h"
#include "../common_queue.h"



AcceptorThread::AcceptorThread(
    Socket &acceptor_skt, 
    Json::Value &config) : acceptor_skt(acceptor_skt),
                           config(config),
                           running(true),
                           client_id(1) {}




#include <iostream>


void AcceptorThread::run() {


    Socket client_skt; 
    Queue receiversQueue;

    MapInfo mapInfo;
    CollisionInfo collisionInfo = mapInfo.load();


    // PROCCESSOR THREAD
    Thread* processorThread = new ServerProcessorThread(receiversQueue, clients, collisionInfo, config);
    processorThread->start(); 


    while (this->running) {
        client_skt = this->acceptor_skt.accept_client();
        // IF NOT VALID ....

        std::cout << "Cliente ACEPTADO" << std::endl;
        SrvClient* client = new SrvClient(client_id, client_skt, receiversQueue, mapInfo);
        std::cout << "ES EL CLIENT: " << std::endl;

        // PUSH
        this->clients.push_back(client);

        // CLEAN
        client_id++;
    }
}



