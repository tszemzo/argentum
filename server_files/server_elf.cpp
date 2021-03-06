#include "server_elf.h"

#define ELF_ID 2

Elf::Elf(Json::Value &config) : 
    Race(config["initialAttributes"].asInt()) {
        this->id = ELF_ID;
        this->strength -= config["elf"]["strength_modifier"].asInt();
        this->agility += config["elf"]["agility_modifier"].asInt();
        this->intelligence += config["elf"]["intelligence_modifier"].asInt();
        this->constitution += config["elf"]["constitution_modifier"].asInt();

        this->life_multiplier = config["elf"]["life_multiplier"].asFloat();
        this->mana_multiplier = config["elf"]["mana_multiplier"].asFloat();
        this->recovery_factor = config["elf"]["recovery_factor"].asFloat();

        this->width = config["elf"]["width"].asInt();
        this->height = config["elf"]["height"].asInt(); 
    }
