#ifndef SPACESHIP_H
#define SPACESHIP_H

// This header files contains:
// * public interface of the module
// * type definitions (strucs, enums)
// * function declarations (only what other files need)
// * contants used by other modules
// * doc for the module's purpose and usage

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

typedef struct {
    float sx;
    float sy;
    float heading;
    float rotation_speed;
    float speed;
    int gone; // is it dead?
    ALLEGRO_COLOR color;
} Spaceship;

Spaceship* spaceship_create(void);
void spaceship_draw(const Spaceship* ship);
void spaceship_destroy(Spaceship* ship);

#endif