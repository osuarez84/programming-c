#include <spaceship.h>
#include <game.h>
#include <stdio.h>
// This file contains:
// * private functions (static)
// * function implementations
// * module state (static variables)
// * internal constants

Spaceship* spaceship_create(void) {
    Spaceship* ship = malloc(sizeof(Spaceship));
    if (ship == NULL) {
        return NULL;
    }
    ship->sx = SCREEN_WIDTH / 2;
    ship->sy = SCREENT_HEIGHT / 2;
    ship->heading = ALLEGRO_PI / 2;
    ship->rotation_speed = ALLEGRO_PI / 100;
    ship->speed = 2;
    ship->gone = FALSE;
    ship->color = al_map_rgb(150, 150, 150);
    return ship;
}


void spaceship_draw(const Spaceship* ship) {
    // // calculate the center of the line
    // float center_x = (ship->sx + ship->sx - 8) / 2.0f; // (x1 + x2) / 2
    // float center_y = (ship->sy + 9 + ship->sy - 11) / 2.0f; // (y1 / y2) / 2
    // float rel_x1 = ship->sx - center_x;
    // float rel_x2 = ship->sx + 8 - center_x;
    // float rel_y1 = ship->sy + 9 - center_y;
    // float rel_y2 = ship->sy - 11 - center_y;

    // ALLEGRO_TRANSFORM transform;
    // al_identity_transform(&transform);
    // al_rotate_transform(&transform, ship->rotation_speed);
    // al_use_transform(&transform);
    
    printf("Heading angle: %.2f\n", ship->heading);
    al_draw_line(ship->sx - 8, ship->sy + 9, ship->sx, ship->sy -11, ship->color, 3.0f);
    al_draw_line(ship->sx, ship->sy - 11, ship->sx + 8, ship->sy + 9, ship->color, 3.0f);
    al_draw_line(ship->sx - 6, ship->sy + 4, ship->sx - 1, ship->sy + 4, ship->color, 3.0f);
    al_draw_line(ship->sx + 6, ship->sy + 4, ship->sx + 1, ship->sy + 4, ship->color, 3.0f);
}

void spaceship_destroy(Spaceship* ship) {
    free(ship);
}
