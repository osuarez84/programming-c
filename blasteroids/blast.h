#ifndef BLAST_H
#define BLAST_H

#include <allegro5/allegro.h>

typedef struct {
    float sx;
    float sy;
    float heading;
    float speed;
    int gone;
    ALLEGRO_COLOR color;
 }Blast;

 #endif