#include "server_movement.h"
#include "server_os_error.h"
#include <iostream>
#include <cstdlib>

#define HEAD_SIZE 20
#define CHARACTER_WIDTH 21
#define CHARACTER_HEIGHT 31
#define WINDOW_SIZE 3200
#define MAX_OFFSET_TOLERANCE 30


Movement::Movement(CollisionInfo &collisionInfo) : collisionInfo(collisionInfo) {
    // ALGORITMO CON POS RANDOM Y CHEQUEO DE COLISIONES
    srand(time(NULL));
    bodyPosX = rand() % (3200 - 0 + 1) + 0;
    bodyPosY = rand() % (3200 - 0 + 1) + 0;

    while(check_map_collision(collisionInfo)) {
        srand(time(NULL));
        bodyPosX = rand() % (3200 - 0 + 1) + 0;
        bodyPosY = rand() % (3200 - 0 + 1) + 0;
    }
}


int Movement::get_horizontal_body_position() const {
    return bodyPosX;
}


int Movement::get_vertical_body_position() const {
    return bodyPosY;
}


void Movement::move_right(int velocity, CollisionInfo &collisionInfo) {

    bodyPosX += velocity;
    last_movement = RIGHT;
    check_out_of_bounds_X(velocity);
    if (check_map_collision(collisionInfo)) {
        bodyPosX -= velocity; 
    }
}

void Movement::move_left(int velocity, CollisionInfo &collisionInfo) {
    bodyPosX -= velocity;
    last_movement = LEFT;
    check_out_of_bounds_X(-velocity);
    if (check_map_collision(collisionInfo)) {
        bodyPosX += velocity;
    }
}

void Movement::move_top(int velocity, CollisionInfo &collisionInfo) {
    bodyPosY -= velocity;
    last_movement = TOP;
    check_out_of_bounds_Y(-velocity);
    if (check_map_collision(collisionInfo)) {
        bodyPosY += velocity;
    }
}

void Movement::move_down(int velocity, CollisionInfo &collisionInfo) {
    bodyPosY += velocity;
    last_movement = DOWN;
    check_out_of_bounds_Y(velocity);
    if (check_map_collision(collisionInfo)) {
        bodyPosY -= velocity;
    }
}

void Movement::move_random(int velocity, CollisionInfo &collisionInfo) {
    srand(time(NULL));
    int randNum = (rand() % 4) + 1;
    std::cout << "Im moving random to " << randNum << std::endl;
    switch (randNum) {
        case 1: return move_right(velocity, collisionInfo);
        case 2: return move_left(velocity, collisionInfo);
        case 3: return move_top(velocity, collisionInfo);
        case 4: return move_down(velocity, collisionInfo);
    }
}

void Movement::stop_moving() {
    last_movement = STAND;
}


_lastMovement Movement::get_facing_direction() {
    return last_movement;
}

bool Movement::is_facing_right(){
    return last_movement == RIGHT;
}

bool Movement::is_facing_left(){
    return last_movement == LEFT;
}

bool Movement::is_facing_top(){
    return last_movement == TOP;
}

bool Movement::is_facing_down(){
    return last_movement == DOWN;
}

bool Movement::is_near_X(int posX){
    int diff = std::abs(bodyPosX - posX);
    std::cout << "Diff in X " << diff << std::endl;
    return diff <= MAX_OFFSET_TOLERANCE;
}

bool Movement::is_near_Y(int posY){
    int diff = std::abs(bodyPosY - posY);
    std::cout << "Diff in Y " << diff << std::endl;
    return diff <= MAX_OFFSET_TOLERANCE;
}

bool Movement::is_near(int posX, int posY) {
    return is_near_X(posX) && is_near_Y(posY);
}

bool Movement::is_safe() {
    return false;
}

void Movement::check_out_of_bounds_X(int velocity){
    if(bodyPosX < 0 || bodyPosX + CHARACTER_WIDTH > WINDOW_SIZE) {
        bodyPosX -= velocity;
    }
}

void Movement::check_out_of_bounds_Y(int velocity){
    if((bodyPosY - HEAD_SIZE) < 0 || bodyPosY + CHARACTER_HEIGHT > WINDOW_SIZE) { 
        bodyPosY -= velocity;
    }
}

bool Movement::check_map_collision(CollisionInfo &collisionInfo) {
    int offsetX = bodyPosX / 128;
    int offsetY = bodyPosY / 128;
    int tileNumber = (offsetY * 25) + offsetX; 
    int tile = collisionInfo.layer[tileNumber];

    if (tile == 0)
        return false;

    std::cout << "BODY POS X: " << bodyPosX << std::endl;
    std::cout << "BODY POS +21: " << bodyPosX + 21 << std::endl;


    std::cout << "ESTAMOS EN UN COLLISION TILE: " << tile << std::endl;
    CollisionTile collisionTile = collisionInfo.tiles[tile];
    
    int collisionX = offsetX * 128 + collisionTile.x;
    int collisionY = offsetY * 128 + collisionTile.y;
    std::cout << "Collision X: " << collisionX << std::endl;
    std::cout << "Collision X + W: " << collisionX + collisionTile.w << std::endl;
    if ((bodyPosX + 21 > collisionX) && (bodyPosX + 21 < collisionX + collisionTile.w)) {
        return true;
    }

    if ((bodyPosX > collisionX) && (bodyPosX < collisionX + collisionTile.w)) {
        return true;
    }

    if ((bodyPosY + 31 > collisionY) && (bodyPosY + 31 < collisionY + collisionTile.h)
        && ((bodyPosX > collisionX) && (bodyPosX + 21 < collisionX + collisionTile.w))) {
        return true;
    }

    return false;
}
