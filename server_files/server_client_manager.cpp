
#include "server_client_manager.h"


ClientManager::ClientManager() {}


void ClientManager::cleanDeadClients() {
    std::vector<SrvClient*> tmp;
    std::vector<SrvClient*>::iterator it = this->clients.begin();
    for (; it != this->clients.end(); ++it) {
        if (!(*it)->is_active()) {
            delete *it;
            continue;
        }
        tmp.push_back(*it);
    }
    this->clients.swap(tmp);
}


void ClientManager::add_client(uint16_t client_id, Socket &skt, MessageToServerQueue &receiversQueue) {
    std::unique_lock<std::mutex> lock(this->m);
    this->cleanDeadClients();
    SrvClient* client = new SrvClient(client_id, std::move(skt), receiversQueue);
    this->clients.push_back(client);
}



void ClientManager::broadcastMessage(ProtocolMessage &updated_msg) {
    std::unique_lock<std::mutex> lock(this->m);
    for (unsigned int i = 0; i < clients.size(); ++i) {
        if (!this->clients[i]->is_active()) continue;
        this->clients[i]->send_message(updated_msg);
    }
}

ClientManager::~ClientManager() {
    for (unsigned int i = 0; i < clients.size(); ++i) {
        clients[i]->stop();
        delete clients[i];
    }
}
