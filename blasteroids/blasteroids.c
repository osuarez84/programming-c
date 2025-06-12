#include <spaceship.h>
#include <game.h>
#include <math.h>



int main() {
    if (!al_init()) {
        perror("Failed to initialize Allegro");
    }

    // init and set up display
    al_set_app_name("Blasteroids");
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREENT_HEIGHT);
    if(display == NULL) {
        perror("Failed to create the display");
    }

    al_set_window_title(display, "Blasteroids");

    // create event queue
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    if (queue == NULL) {
        perror("Failed to create event queue");
    }

    // setup timer for consistent frame rate
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    if (timer == NULL) {
        perror("Failed to create timer");
    }

    // init the keyboard
    if(!al_install_keyboard()) {
        perror("Failed to initialize the keyboard");
    }
    
    ALLEGRO_KEYBOARD_STATE key_state;

    // register event sources
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    int running = TRUE;
    ALLEGRO_EVENT event;


    // Init here all the objects
    Spaceship* ship = spaceship_create();
    if (ship == NULL) {
        perror("Failed to create ship object");
    }
    
    // Game loop
    while(running) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                // Update here all the objects
                al_get_keyboard_state(&key_state);
                if (al_key_down(&key_state, ALLEGRO_KEY_UP)) {
                    ship->sy -= ship->speed;
                }
                if (al_key_down(&key_state, ALLEGRO_KEY_DOWN)) {
                    ship->sy += ship->speed;
                }
                if (al_key_down(&key_state, ALLEGRO_KEY_LEFT)) {
                    ship->sx -= ship->speed;
                }
                if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT)) {
                    ship->sx += ship->speed;
                }
                if (al_key_down(&key_state, ALLEGRO_KEY_A)) {
                    ship->heading = fmod(ship->heading + ship->rotation_speed, 2*ALLEGRO_PI);
                }
                if (al_key_down(&key_state, ALLEGRO_KEY_F)) {
                    ship->heading = fmod(ship->heading - ship->rotation_speed, 2*ALLEGRO_PI);
                    if (ship->heading < 0) {
                        ship->heading += 2.0f*ALLEGRO_PI;
                    }
                }

                // Clear the screen
                al_clear_to_color(al_map_rgb(0, 0, 0));

                // Render here all the objects
                spaceship_draw(ship);

                // Update display
                al_flip_display();
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = FALSE;
                break;
        }
    }

    
    // Cleanup before exiting
    spaceship_destroy(ship);

    // Cleanup Allegro resources
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    al_destroy_display(display);
    return 0;
}