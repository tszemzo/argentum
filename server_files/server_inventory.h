#ifndef _SERVER_INVENTORY
#define _SERVER_INVENTORY

#include <vector>
#include "server_item.h"

/* Clase que representa a un item del juego */
class Inventory {
private:
    std::vector<Item> items;
    unsigned int max_size;

public:
    // Contructor, recibe el tamaño del inventario
    explicit Inventory(int size);

    // Agrega un item al inventario
    void add_item(Item& item);

    // Remueve un item del inventario
    void remove_item(int16_t id);

    // Dropea todos los items del inventario populando el mundo de items
    // Y recibiendo las posiciones del jugador como parametro
    void drop_items(int16_t posX, int16_t posY, std::vector<Item> &worldItems);

    // Devuelve el tam del inventario
    unsigned int size();

    // Boleana, verdadera si posee el item
    bool has(int16_t id);

    // Booleana, esta lleno el inventario
    bool is_full();
};


#endif //_SERVER_ITEM
