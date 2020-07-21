
#include "server_game_loop_thread.h"
#include "server_processor_thread.h"
#include "../common_files/common_mapinfo.h"

ServerProcessorThread::ServerProcessorThread(
    MessageToServerQueue &receiversQueue,
    ClientManager &clientManager,
    CollisionInfo &collisionInfo,
    Json::Value &config) : receiversQueue(receiversQueue),
                            clientManager(clientManager),
                            collisionInfo(collisionInfo),
                            config(config),
                            running(true) {}



void ServerProcessorThread::addingHardcodedItems(ServerWorld &world) {
    Sword i(config);
    i.set_posX(100);
    i.set_posY(100);
    i.set_amount(1);
    world.items.push_back(i);

    IronShield p(config);
    p.set_posX(150);
    p.set_posY(150);
    p.set_amount(1);
    world.items.push_back(p);

    GnarledStaff j(config);
    j.set_posX(200);
    j.set_posY(200);
    j.set_amount(1);
    world.items.push_back(j);

    GnarledStaff k(config);
    k.set_posX(30);
    k.set_posY(30);
    k.set_amount(5);
    world.items.push_back(k);

    CrimpStaff z(config);
    z.set_posX(50);
    z.set_posY(50);
    z.set_amount(1);
    world.items.push_back(z);

    Axe axe(config);
    axe.set_posX(100);
    axe.set_posY(200);
    axe.set_amount(1);
    world.items.push_back(axe);

    Axe hammer(config);
    hammer.set_posX(100);
    hammer.set_posY(300);
    hammer.set_amount(1);
    world.items.push_back(hammer);

    SimpleBow sb(config);
    sb.set_posX(100);
    sb.set_posY(400);
    sb.set_amount(1);
    world.items.push_back(sb);

    Hood hood(config);
    hood.set_posX(100);
    hood.set_posY(500);
    hood.set_amount(1);
    world.items.push_back(hood);

    PlateArmor armor(config);
    armor.set_posX(300);
    armor.set_posY(300);
    armor.set_amount(1);
    world.items.push_back(armor);

    LifePotion shield(config);
    shield.set_posX(200);
    shield.set_posY(100);
    shield.set_amount(1);
    world.items.push_back(shield);

    ManaPotion mana(config);
    mana.set_posX(75);
    mana.set_posY(75);
    mana.set_amount(1);
    world.items.push_back(mana);

    LifePotion life(config);
    life.set_posX(125);
    life.set_posY(100);
    life.set_amount(1);
    world.items.push_back(life);
}



void ServerProcessorThread::run() {

    ProtocolTranslator protocol_translator(config, collisionInfo);
    ServerWorld serverWorld;
    
    Banker banker(collisionInfo.get_banker_posX(), collisionInfo.get_banker_posY());
    serverWorld.add(banker);

    Priest priest(collisionInfo.get_priest_posX(), collisionInfo.get_priest_posY());
    serverWorld.add(priest);

    GameLoopThread* game_loop = new GameLoopThread(receiversQueue);
    game_loop->start();

    this->addingHardcodedItems(serverWorld); // This might be deleted
    
    while (running) {
        ProtocolMessage client_response;
        try {
            MessageToServer received_msg = this->receiversQueue.pop();
            protocol_translator.translate(received_msg, client_response, serverWorld);
            if (client_response.id_message != NOTHING)
            this->clientManager.broadcastMessage(client_response);
        } catch (QueueNotOperatingException& e) {
            this->running = false;
        }
    }

    game_loop->stop();
    game_loop->join();
    delete game_loop;
}
