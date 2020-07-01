#include <math.h>
#include <iostream>
#include <stdio.h>
#include "server_character.h"

#define NO_LIFE 0
#define NO_DAMAGE 0
#define INITIAL_GOLD 0
#define INITIAL_LEVEL 1
#define CRITICAL_MULTIPLIER 2
#define LOW_CONSTANT_EXP 0
#define HIGH_CONSTANT_EXP 10

Character::Character(size_t id, Json::Value &config, CharacterClass& character_class, Race& race, CollisionInfo &collisionInfo) : 
    config(config),
    character_class(character_class),
    race(race), 
    life(race.get_constitution(), character_class.get_life_multiplier(), race.get_life_multiplier()), 
    mana(race.get_intelligence(), character_class.get_mana_multiplier(), race.get_mana_multiplier()),
    experience(config["experience"]["difficulty_constant"].asUInt(), config["experience"]["level_multiplier"].asFloat()),
    inventory(config["inventory"]["max_items"].asUInt()),
    collisionInfo(collisionInfo) {
    this->id = id;
    this->gold = INITIAL_GOLD;
    this->level = INITIAL_LEVEL;
    this->alive = true;
    this->newbie = true;
}

int Character::get_life() {
    return life.current();
}

int Character::get_max_life() {
    return life.max();
}

int Character::get_mana() {
    return mana.current();
}

int Character::get_level() {
    return level;
}

void Character::recover_life(int life_points) {
    life.add(life_points);
}

void Character::recover_mana(int mana_points) {
    mana.add(mana_points);
}

bool Character::is_alive() {
    return alive;
}

void Character::take_off_life(int life_points) {
    life.subtract(life_points);
}

void Character::take_off_mana(int mana_points) {
    mana.subtract(mana_points);
}

void Character::drop() {
    std::cout << "Dropping gold & items" << std::endl;
    // unequip everything;
    drop_gold();
    drop_items();
}

void Character::drop_item(Item& item) {
    std::cout << "Dropping an item" << std::endl;
    inventory.remove_item(item);
}

const int Character::max_secure_gold() {
    return config["gold"]["secure_gold_constant"].asInt() 
    * (pow(level, config["gold"]["power_constant"].asFloat()));
}

const int Character::max_gold() {
    const int excess = max_secure_gold() * config["gold"]["extra_gold_rate"].asFloat();
    return max_secure_gold() + excess;
}

void Character::take_gold(int amount) {
    // TODO: We should drop the excess in this case
    std::cout << "Current max gold is: "<< max_gold() << std::endl;
    if (gold + amount >= max_gold()) {
        gold = max_gold();
        // drop_excess()
    } else {
        gold += amount;
    }
}

int Character::drop_gold() {
  // TODO: heres just the logic, we should send some message to the client, possibly
  // We are not going to return anything
    if (gold > max_secure_gold()) {
        const int dropped_gold = gold - max_secure_gold();
        gold -= dropped_gold;
        std::cout << "We are dropping gold: "<< dropped_gold << std::endl;
        return dropped_gold;
    }
    return 0;
}

void Character::take_item(Item& item) {
    // TODO: heres just the logic, we should send some message to the client
    inventory.add_item(item);
}

void Character::drop_items() {
    inventory.drop_items();
}

void Character::equip_life_potion(Potion& item) {
    int recovery = item.get_recovery_points();
    if (inventory.has(item)) {
        life.add(recovery);
    } 
}

void Character::equip_mana_potion(Potion& item) {
    int recovery = item.get_recovery_points();
    if (inventory.has(item)) {
        mana.add(recovery);
    } 
}

void Character::equip_weapon(Weapon& item) {
    if (inventory.has(item)) {
        equipment.equip_weapon(item);
    } 
}

void Character::equip_armor(Armor& item) {
    if (inventory.has(item)) {
        equipment.equip_armor(item);
    }
}

void Character::equip_shield(Shield& item) {
    if (inventory.has(item)) {
        equipment.equip_shield(item);
    }
}

void Character::equip_helmet(Helmet& item) {
    if (inventory.has(item)) {
        equipment.equip_helmet(item);
    }
}

bool Character::is_critical() {
    int critical_percentage = config["attack"]["critical_probability"].asFloat() * 100;
    srand (time(NULL));
    int critical_chances = rand() % 100 + 1;
    if (critical_chances <= critical_percentage) return true;
    return false;
}

void Character::attack(Character& other) {
    // TODO: si !es a distancia el arma, chequear que este al lado
    // TODO: Check fairplay
    int damage = equipment.get_weapon_damage();
    if (is_critical()) damage *= CRITICAL_MULTIPLIER;
    if (equipment.is_weapon_magical()) {
        int mana_consumption = equipment.get_weapon_consumption();
        take_off_mana(mana_consumption);
    }
    std::cout << "Ataque::Dano:: " << damage << std::endl;
    int final_damage = other.defense(damage);
    get_experience(other, final_damage);
    update_level();
}

bool Character::evade_attack() {
    srand (time(NULL));
    double evasion_chances = ((double) rand() / (RAND_MAX));
    double evasion_power = pow(evasion_chances, race.get_agility());
    bool evade = evasion_power < config["defense"]["evasion_constant"].asDouble();
    return evade;
}

int Character::defense(int damage) {
    if (evade_attack()) return NO_DAMAGE;
    int defense = equipment.get_equipment_defense();
    if (damage <= defense) return NO_DAMAGE;
    int final_damage = damage - defense;
    take_off_life(final_damage);
    if (life.current() == NO_LIFE) alive = false;
    std::cout << "Defensa:: " << defense << std::endl;
    return final_damage;
}

int Character::experience_formula(Character& other) {
    return std::max(other.get_level() - level + HIGH_CONSTANT_EXP, LOW_CONSTANT_EXP);
}

int Character::get_extra_experience(Character& other) {
    srand (time(NULL));
    float min = config["experience"]["min_extra_probability"].asFloat();
    float max = config["experience"]["max_extra_probability"].asFloat();
    float random = ((float) rand()) / (float) RAND_MAX;
    float ponderation = min + (random * (max - min));
    std::cout << "ExtraPonderation:: " << ponderation << std::endl;
    int extra_exp = ponderation * other.get_max_life() * experience_formula(other);
    std::cout << "ExtraExperienceWon:: " << extra_exp << std::endl;
    return extra_exp;
}

void Character::get_experience(Character& other, int damage) {
    int won_experience = damage * experience_formula(other);
    std::cout << "ExperienceWon:: " << won_experience << std::endl;
    if (!other.is_alive()) {
        won_experience += get_extra_experience(other);
    }
    experience.add(won_experience);
}

void Character::update_level() {
    while (experience.current() >= experience.max()) {
        level++;
        // Update mana & life
        // Update Newbie
        experience.subtract(experience.max());
        experience.set_new_max(level);
        std::cout << "NewMaxExp:: " << experience.max() << std::endl;
    }
}

void Character::move_right(int velocity) {
    movement.move_right(velocity, collisionInfo);
}

void Character::move_left(int velocity) {
    movement.move_left(velocity, collisionInfo);
}

void Character::move_top(int velocity) {
    movement.move_top(velocity, collisionInfo);
}

void Character::move_down(int velocity) {
    movement.move_down(velocity, collisionInfo);
}

int Character::get_body_pos_X() {
    return movement.get_horizontal_body_position();
}

int Character::get_head_pos_X() {
    return movement.get_horizontal_head_position();
}

int Character::get_body_pos_Y() {
    return movement.get_vertical_body_position();
}

int Character::get_head_pos_Y() {
    return movement.get_vertical_head_position();
}

