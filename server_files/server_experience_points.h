#ifndef _SERVER_EXPERIENCE_POINTS
#define _SERVER_EXPERIENCE_POINTS

/* Clase que representa a los puntos de experiencia de un personaje */
class ExperiencePoints {
private:
    int difficulty_constant;
    float level_multiplier;
    int current_exp;
    int max_exp;

public:
    // Contructor
    ExperiencePoints(int difficulty_constant, float level_multiplier);

    // Disminuye la experiencia en points
    void subtract(int points);

    // Aumenta la experiencia en _points
    void add(int points);
    
    // Devuelve la experiencia actual
    int current();

    // Devuelve la maxima del nivel
    int max();

    // Setter de la max experiencia para el nivel recibido
    void set_new_max(int level);
};


#endif //_SERVER_EXPERIENCE_POINTS