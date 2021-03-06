#ifndef _SERVER_MOVEMENT
#define _SERVER_MOVEMENT

#include <stdint.h>
#include "../common_files/common_collision_info.h"

// Which was the last movement.
enum _lastMovement {
    STAND,
    LEFT,
    RIGHT,
    TOP,
    DOWN
};

/* Clase encargada de la movilidad de un personaje. */
class Movement {
private:
    CollisionInfo &collisionInfo;
    int16_t bodyPosX;
    int16_t bodyPosY;
    _lastMovement last_movement;
  
    // No copiable
    Movement(const Movement&) = delete;
    Movement& operator=(const Movement&) = delete;

public:
    Movement(CollisionInfo &collisionInfo);

    // Devuelve un int indicando la posicion en X del cuerpo.
    int16_t get_horizontal_body_position() const;

    // Devuelve un int indicando la posicion en Y del cuerpo.
    int16_t get_vertical_body_position() const;

    // Setea el movimiento del personaje hacia la derecha
    void move_right(int velocity);

    // Setea el movimiento del personaje hacia la izquierda
    void move_left(int velocity);

    // Setea el movimiento del personaje hacia la derecha
    void move_top(int velocity);

    // Setea el movimiento del personaje hacia la izquierda
    void move_down(int velocity);

    // Setea el movimiento del personaje hacia una direccion random
    void move_random(int velocity);

    // Acerca al personaje de costado hacia X Y
    void move_aside(int velocity, int16_t posX);

    // Acerca al personaje en vertical hacia X Y
    void move_vertical(int velocity, int16_t posY); 

    // Acerca al personaje hacia la posicion posX, posY
    void move_to(int velocity, int16_t posX, int16_t posY);

    // Detiene el movimiento.
    void stop_moving();

    _lastMovement get_facing_direction() const;
  
    // Booleano que devuelve verdadero si posX y posY estan cerca del personaje
    bool is_near(const int posX, const int posY) const;

    // Booleano que devuelve verdadero si posX esta cerca del personaje bodyPosX
    bool is_near_X(const int posX) const;

    // Booleano que devuelve verdadero si posY esta cerca del personaje bodyPosY
    bool is_near_Y(const int posY) const;

    // Booleano que devuelve verdadero si posX y posY son atacables
    bool is_attackable(const int16_t posX, const int16_t posY) const;

    // Booleano que devuelve verdadero si posX es atacable
    bool is_attackable_X(const int16_t posX) const;

    // Booleano que devuelve verdadero si posY es atacable
    bool is_attackable_Y(const int16_t posY) const;

    // Booleano que devuelve verdadero si la zona es segura o falso si no.
    bool is_safe() const;

    // Devuelve true si el personaje está mirando hacia la derecha, false en caso contrario.
    bool is_facing_right() const;

    // Devuelve true si el personaje está mirando hacia la izquierda, false en caso contrario.
    bool is_facing_left() const;

    // Devuelve true si el personaje está mirando hacia arriba, false en caso contrario.
    bool is_facing_top() const;

    // Devuelve true si el personaje está mirando hacia abajo, false en caso contrario.
    bool is_facing_down() const;

    // Invierte hacia donde esta mirando el personaje, se usa en caso de que colisione
    void invert_body_facing();

    // Corrige la posicion en X si el personaje se va de los limites del mapa
    void check_out_of_bounds_X(const int velocity);

    // Corrige la posicion en Y si el personaje se va de los limites del mapa
    void check_out_of_bounds_Y(const int velocity);

    // Chequea las colisiones estaticas contra el mapa del personaje
    bool check_map_collision() const;

    // Chequea las colisiones estaticas contra los banqueros del mapa
    bool banker_collision() const;

    // Chequea las colisiones estaticas contra los sacerdotes del mapa
    bool priest_collision() const;
};


#endif //_SERVER_MOVEMENT
