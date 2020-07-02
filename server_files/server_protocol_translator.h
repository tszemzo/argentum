#include <msgpack.hpp>
#include <jsoncpp/json/json.h>
#include "../common_protocol_message.h"
#include "server_character.h"
#include "server_helmet.h"
#include "server_armor.h"
#include "server_helmet_factory.h"
#include "server_armor_factory.h"
#include "common_collision_info.h"

#ifndef _PROTOCOL_TRANSLATOR
#define _PROTOCOL_TRANSLATOR

// Received from the client
#define PROTOCOL_MOVE 1
#define PROTOCOL_ATTACK 2
#define PROTOCOL_EQUIP_HELMET 3
#define PROTOCOL_EQUIP_ARMOR 4

// Sending to the client
#define PROTOCOL_MOVE_CONFIRM 20
#define PROTOCOL_HELMET_CONFIRM 30
#define PROTOCOL_ARMOR_CONFIRM 31
#define PROTOCOL_WEAPON_CONFIRM 32
#define PROTOCOL_SHIELD_CONFIRM 33

/* Clase que se encarga de ejecutar los codigos recibidos y matchearlos a una
 * función del personaje.
 */
class ProtocolTranslator {
private:
    Json::Value &config;
    CollisionInfo &collisionInfo;

    ProtocolMessage move_event(ProtocolMessage& msg, Character& character);
    ProtocolMessage equip_helmet_event(ProtocolMessage& msg, Character& character);
    ProtocolMessage equip_armor_event(ProtocolMessage& msg, Character& character);
    ProtocolMessage create_character(ProtocolMessage& msg, ServerWorld &world);

public:
    ProtocolTranslator(Json::Value &config, CollisionInfo &collisionInfo);

    // Transforma el codigo recibido un mensaje del protocolo
    ProtocolMessage translate(ProtocolMessage& msg, Character& character);
};

#endif //_PROTOCOL_TRANSLATOR
