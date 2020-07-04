#ifndef _SERVER_MANA_POINTS
#define _SERVER_MANA_POINTS

/* Clase que representa a los puntos de mana de un personaje */
class ManaPoints {
private:
    int intelligence;
    float class_multiplier, race_multiplier;
    int current_mana, max_mana;

public:
    // Contructor, recibe la inteligencia de la raza
    ManaPoints(int intelligence, float class_multiplier, float race_multiplier);

    // Disminuye la mana en mana_points
    void subtract(int mana_points);

    // Aumenta la mana en mana_points
    void add(int mana_points);
    
    // Devuelve la mana actual
    int current();

    // Setter de la max mana para el nivel recibido
    void set_new_max(int level);
};


#endif //_SERVER_MANA_POINTS