#include <stdint.h>
#include <iostream>

#include "server_world.h"
#include "server_protocol_translator.h"

#include "server_elf.h"
#include "server_cleric.h"

ProtocolTranslator::ProtocolTranslator(
    Json::Value &config, 
    CollisionInfo &collisionInfo) : config(config),
                                    collisionInfo(collisionInfo) {}


ProtocolMessage ProtocolTranslator::translate(ProtocolMessage& msg, ServerWorld& world) {
    int code = msg.id_message;
    // Character character = world.get(msg.id_player);
    switch (code) {
        case 65: return create_character(msg, world);
        case PROTOCOL_MOVE: return move_event(msg, character);
        case PROTOCOL_EQUIP_HELMET: return equip_helmet_event(msg, character);
        case PROTOCOL_EQUIP_ARMOR: return equip_armor_event(msg, character);
    }
    return std::move(msg);
}

ProtocolMessage ProtocolTranslator::equip_armor_event(ProtocolMessage &msg, Character& character) {
    int armor_id = msg.character.armorId;
    ArmorFactory factory;
    Armor armor = factory.make_armor(armor_id, config);
    character.equip_armor(armor);
    msg.id = PROTOCOL_ARMOR_CONFIRM;

    std::cout << "ID: " << msg.id << std::endl;
    std::cout << "Updated Armor ID: " << msg.character.armorId << std::endl;

    return std::move(msg);
}

ProtocolMessage ProtocolTranslator::equip_helmet_event(ProtocolMessage &msg, Character& character) {
    int helmet_id = msg.character.helmetId;
    HelmetFactory factory;
    Helmet helmet = factory.make_helmet(helmet_id, config);
    character.equip_helmet(helmet);
    msg.id = PROTOCOL_HELMET_CONFIRM;

    std::cout << "ID: " << msg.id << std::endl;
    std::cout << "Updated Helmet ID: " << msg.character.helmetId << std::endl;

    return std::move(msg);
}

ProtocolMessage ProtocolTranslator::move_event(ProtocolMessage &msg, Character& character) {
    int velX = msg.character.velX;
    int velY = msg.character.velY;

    if (velX > 0) {
        character.move_right(velX);
    }
    if (velX < 0) {
        character.move_left(velX);;
    }
    if (velY > 0) {
        character.move_top(velY);
    }
    if (velY < 0) {
        character.move_down(velY);
    }
    msg.character.bodyPosX = character.get_body_pos_X();
    msg.character.headPosX = character.get_head_pos_X();
    msg.character.bodyPosY = character.get_body_pos_Y();
    msg.character.headPosY = character.get_head_pos_Y();
    msg.id = PROTOCOL_MOVE_CONFIRM;

    std::cout << "ID: " << msg.id << std::endl;
    std::cout << "Updated BODY pos X: " << msg.character.bodyPosX << std::endl;
    std::cout << "Updated BODY pos Y: " << msg.character.bodyPosY << std::endl;
    std::cout << "Updated HEAD pos X: " << msg.character.headPosX << std::endl;
    std::cout << "Updated HEAD pos Y: " << msg.character.headPosY << std::endl;

    return std::move(msg);
}


ProtocolMessage ProtocolTranslator::create_character(ProtocolMessage& msg, ServerWorld &world) {
    
    Elf race(config);
    Cleric c(config);
    Character* character = new Character(msg.id_player, config, c, race, collisionInfo);
    world.add(msg.id_player, character);

    msg.id_message = 66;
    

}
