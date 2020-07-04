#ifndef _CLIENT_ZOMBIE
#define _CLIENT_ZOMBIE

#include <stdint.h>
#include <SDL2/SDL.h>

#include "client_npc.h"



class Zombie: public NPC {

    // virtual bool load_pictures(const char* picture_path);
    virtual void load_front_walking_sprite();  
    virtual void load_back_walking_sprite();
    virtual void load_left_walking_sprite();
    virtual void load_right_walking_sprite();
    virtual void set_sprites();
    SDL_Rect leftOrientation[5];
    SDL_Rect rightOrientation[5];
    SDL_Rect frontOrientation[6];
    SDL_Rect backOrientation[6];
    public:
        Zombie(int16_t id, SDL_Renderer* gRenderer);

};




#endif