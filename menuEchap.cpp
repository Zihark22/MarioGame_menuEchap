/*

g++ menuEchap.cpp -o menu.o -lallegro -lallegro_main -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf

./menu


*/

#include <iostream>
#include <string> 

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

const int WIDTH = 640;
const int HEIGHT = 480;
const int NBR_BOUT = 3;

const string boutons[NBR_BOUT] = {"RESUME" , "CONTROLS" , "EXIT"};

int main(int argc, char **argv)
{
    // Initialisation d'Allegro
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // Création de la fenêtre
    ALLEGRO_DISPLAY* display = al_create_display(WIDTH, HEIGHT);
    al_set_window_title(display, "Game");

    // Création de la file d'événements
    ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_keyboard_event_source());

    // Image menu echap
    ALLEGRO_BITMAP *background = al_load_bitmap("super-mario-nintendo.jpg");
    ALLEGRO_BITMAP *jeu = al_load_bitmap("Super_Mario_Bros_Movie.jpg");
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

    // Font
    ALLEGRO_FONT* font = al_load_font("Arial.ttf", 36, 0);
    

    // Initialisation de l'affichage
    al_draw_scaled_bitmap(jeu, 0, 0, al_get_bitmap_width(jeu), al_get_bitmap_height(jeu), 0, 0, WIDTH, HEIGHT, 0);
    al_flip_display();

    int boutonSelected = 0;
    int j=1;
    const float depl = HEIGHT/NBR_BOUT/2-5;

    // Boucle principale du jeu
    bool done = false;
    bool menu = false;
    while (!done)
    {
        // Gestion des événements
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventQueue, &ev);

        switch (ev.type)
        {
            // Gestion des touches du clavier
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done=true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (ev.keyboard.keycode)
                {
                    case ALLEGRO_KEY_ESCAPE:
                        menu=true;
                        break;
                    case ALLEGRO_KEY_UP:
                        if(menu) {
                            boutonSelected--;
                            if(boutonSelected<1)
                                boutonSelected=NBR_BOUT;
                        }
                        break;
                    case ALLEGRO_KEY_DOWN:
                        if(menu) {
                            boutonSelected++;
                            if(boutonSelected>NBR_BOUT)
                                boutonSelected=1;
                        }
                        break;
                    case ALLEGRO_KEY_ENTER:
                        if(menu) {
                            switch(boutonSelected)
                            {
                                case 1 :
                                    boutonSelected=0;
                                    menu=false;
                                    break;
                                case 2 :
                                    cout << "Controls : " << endl;
                                    break;
                                case 3 :
                                    done=true;
                                    break;
                            }
                        }
                        break;
                }
                break;
        }

        if(menu) 
        {
            // Dessiner l'image et le bouton selectionné
            al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, WIDTH, HEIGHT, 0);
            if(boutonSelected!=0)
                al_draw_filled_rectangle(0, (boutonSelected-1)*HEIGHT/NBR_BOUT, WIDTH, boutonSelected*HEIGHT/NBR_BOUT, al_map_rgba(255, 255, 255, 200)); // blanc transparent
            
            j=1;
            for (int i = 1; i <= NBR_BOUT; ++i) {
                al_draw_text(font, al_map_rgb(255, 0, 0), WIDTH/2, j*depl, ALLEGRO_ALIGN_CENTER, boutons[i-1].c_str());
                j+=2;
            }
        }
        else
            al_draw_scaled_bitmap(jeu, 0, 0, al_get_bitmap_width(jeu), al_get_bitmap_height(jeu), 0, 0, WIDTH, HEIGHT, 0);

        // Rafraîchir
        al_flip_display();
    }

    // Clean up
    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);

    return 0;
}

