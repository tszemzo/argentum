
#include "client_gnome.h"

Gnome::Gnome(
    SDL_Renderer* gRenderer, 
    int16_t id, 
    int bodyPosX, 
    int bodyPosY) : ShortPlayer(
                        gRenderer, 
                        "media/images/gnomo.png", 
                        id,
                        bodyPosX, 
                        bodyPosY) {}
