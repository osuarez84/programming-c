#include <asteroid.h>
#include <game.h>



Asteroid* asteroid_create(void) {
    Asteroid* ast = malloc(sizeof(Asteroid));
    if (ast == NULL) {
        return NULL;
    }
    ast->sx = // random
    ast->sy = // random
    ast->heading = ALLEGRO_PI / 2;
    ast->twist = 0;
    ast->speed = 2;
    ast->rot_velocity = ALLEGRO_PI / 100;
    ast->scale = 0.2;
    ast->gone = FALSE;
    ast->color = al_map_rgb(150, 150, 150);
    return ast;
}


void asteorid_draw(const Asteroid* ast) {
    al_draw_line(-20, 20, -25, 5, ast->color, 2.0f);
    //TODO
}