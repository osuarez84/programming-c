#ifndef ASTEROID_H
#define ASTEROID_H

#include <allegro5/allegro.h>


typedef struct {
    float sx;
    float sy;
    float heading;
    float twist;
    float speed;
    float rot_velocity;
    float scale;
    int gone;
    ALLEGRO_COLOR color;
} Asteroid;

Asteroid* asteroid_create(void);
void asteroid_draw(const Asteroid* ast);
void asteroid_destroy(Asteroid* ast);


#endif