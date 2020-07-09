#ifndef _SERVER_ATTACKABLE
#define _SERVER_ATTACKABLE

/* 
 * Clase que representa a un atacable del juego.
 * Va a funcionar como interfaz para poder hacer
 * polimorfismo entre los NPCs y los Characters
 */
class Attackable {
private:
    void get_experience(Attackable& other, int damage);
    virtual bool can_attack(Attackable& other) = 0;

public:
    virtual bool is_newbie() = 0;
    virtual bool is_alive() = 0;
    virtual int get_max_life() = 0;
    virtual int get_level() = 0;
    virtual int get_body_pos_X() const = 0;
    virtual int get_body_pos_Y() const = 0;
    virtual int defense(int damage) = 0;
    virtual void attack(Attackable& other) = 0;
};


#endif //_CHARACTER