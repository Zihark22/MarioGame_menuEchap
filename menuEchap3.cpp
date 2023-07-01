/*

g++ menuEchap3.cpp -o menu3.o -lallegro -lallegro_main -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf -lallegro_color

./menu3

*/

#include <iostream>
#include <string> 

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>

using namespace std;

const int WIDTH = 640;
const int HEIGHT = 480;
const int NBR_BOUT = 3;

const string boutons[NBR_BOUT] = {"RESUME" , "CONTROLS" , "EXIT"};

typedef struct
{
    string nom;
    float posX;
    float posY;
    float w;
    float h;
    ALLEGRO_FONT* font;
    ALLEGRO_COLOR couleurTxt;
    ALLEGRO_COLOR couleurRect;
} bouton;

bool MouseOnButton(int mouseX, int mouseY, bouton monBut) {
    if(mouseX>monBut.posX && mouseX<monBut.posX+monBut.w && mouseY>monBut.posY && mouseY<monBut.posY+monBut.h)
        return true;
    else
        return false;
}

int main(int argc, char **argv)
{
    // Initialisation d'Allegro
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // Création de la fenêtre
    ALLEGRO_DISPLAY* display = al_create_display(WIDTH, HEIGHT);
    al_set_window_title(display, "Game");

    // Création de la file d'événements
    ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_register_event_source(eventQueue, al_get_display_event_source(display));

    ALLEGRO_MOUSE_STATE mouse_state;

    // Image menu echap
    ALLEGRO_BITMAP *background = al_load_bitmap("super-mario-nintendo.jpg");
    ALLEGRO_BITMAP *jeu = al_load_bitmap("Super_Mario_Bros_Movie.jpg");
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

    // Font
    ALLEGRO_FONT* arial18 = al_load_font("Arial.ttf", 18, 0);
    ALLEGRO_FONT* arial36 = al_load_font("Arial.ttf", 36, 0);
    ALLEGRO_FONT* arial54 = al_load_font("Arial.ttf", 54, 0);

    // Color
    ALLEGRO_COLOR color_black_tr = al_map_rgba(0, 0, 0, 200);
    ALLEGRO_COLOR color_grey_tr = al_map_rgba(55, 55, 55, 200);
    ALLEGRO_COLOR color_white_tr = al_map_rgba(255, 255, 255, 200);
    ALLEGRO_COLOR color_red_tr   = al_map_rgba(255, 0, 0, 200);
    ALLEGRO_COLOR color_green_tr = al_map_rgba(0, 255, 0, 200);
    ALLEGRO_COLOR color_blue_tr  = al_map_rgba(0, 0, 255, 200);
    ALLEGRO_COLOR color_jaune_tr = al_map_rgba(255, 255, 0, 200);

    ALLEGRO_COLOR color_black = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR color_white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR color_red   = al_map_rgb(255, 0, 0);
    ALLEGRO_COLOR color_green = al_map_rgb(0, 255, 0);
    ALLEGRO_COLOR color_blue  = al_map_rgb(0, 0, 255);
    ALLEGRO_COLOR color_jaune = al_map_rgb(255, 255, 0);
    
    // Initialisation de l'affichage
    al_draw_scaled_bitmap(jeu, 0, 0, al_get_bitmap_width(jeu), al_get_bitmap_height(jeu), 0, 0, WIDTH, HEIGHT, 0);
    al_flip_display();

    int boutonSelected = 0;
    int i=0;
    const float depl = HEIGHT/NBR_BOUT/2-5;
    int x=0, y=0;

    // Liste des boutons
    bouton listeBut[NBR_BOUT];
    listeBut[0] = (bouton) {"CONTINUER" , WIDTH/4, HEIGHT/(NBR_BOUT+2), 2*WIDTH/4, HEIGHT/(NBR_BOUT+2), arial36, color_red, color_grey_tr};
    listeBut[1] = (bouton) {"COMMANDES" , WIDTH/4, 2*HEIGHT/(NBR_BOUT+2)+20, 2*WIDTH/4, HEIGHT/(NBR_BOUT+2), arial36, color_red, color_grey_tr};
    listeBut[2] = (bouton) {"QUITTER" , WIDTH/4, 3*HEIGHT/(NBR_BOUT+2)+40, 2*WIDTH/4, HEIGHT/(NBR_BOUT+2), arial36, color_red, color_grey_tr};

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
                        menu=!menu;
                        break;
                    case ALLEGRO_KEY_UP:
                        if(menu) {
                            boutonSelected--;
                            if(boutonSelected<0)
                                boutonSelected=NBR_BOUT;
                            for (i = 0; i < NBR_BOUT; ++i) {
                                if(i==boutonSelected) {
                                    listeBut[i].couleurTxt=color_jaune;
                                    listeBut[i].couleurRect=color_black;
                                    boutonSelected=i;
                                }
                                else {
                                    listeBut[i].couleurTxt=color_red;
                                    listeBut[i].couleurRect=color_grey_tr;
                                }
                            }
                        }
                        break;
                    case ALLEGRO_KEY_DOWN:
                        if(menu) {
                            boutonSelected++;
                            if(boutonSelected>=NBR_BOUT)
                                boutonSelected=0;
                            for (i = 0; i < NBR_BOUT; ++i) {
                                if(i==boutonSelected) {
                                    listeBut[i].couleurTxt=color_jaune;
                                    listeBut[i].couleurRect=color_black;
                                    boutonSelected=i;
                                }
                                else {
                                    listeBut[i].couleurTxt=color_red;
                                    listeBut[i].couleurRect=color_grey_tr;
                                }
                            }
                        }
                        break;
                    case ALLEGRO_KEY_ENTER:
                        if(menu) {
                            switch(boutonSelected)
                            {
                                case 0 :
                                    boutonSelected=-1;
                                    menu=false;
                                    break;
                                case 1 :
                                    cout << "Controls : " << endl;
                                    break;
                                case 2 :
                                    done=true;
                                    break;
                                default :
                                    break;
                            }
                        }
                        break;
                }
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(ev.mouse.button==1) {
                    // fprintf(stdout, "Vous avez cliqué à gauche avec la souris.\n");
                    if(menu) {
                        switch(boutonSelected)
                        {
                            case 0 :
                                boutonSelected=-1;
                                menu=false;
                                break;
                            case 1 :
                                cout << "Controls : " << endl;
                                break;
                            case 2 :
                                done=true;
                                break;
                            default :
                                break;
                        }
                    }
                }
                else if(ev.mouse.button==2) {
                    //fprintf(stdout, "Vous avez cliqué à droite avec la souris.\n");
                }
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                //fprintf(stdout, "Vous avez relâché la souris. Mouse button %d up at (%d, %d)\n", ev.mouse.button, ev.mouse.x, ev.mouse.y);
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                al_get_mouse_state(&mouse_state);
                if(abs(x-mouse_state.x)>10 || abs(y-mouse_state.y)>10)
                {
                    x = mouse_state.x;
                    y = mouse_state.y;
                    for (i = 0; i < NBR_BOUT; ++i) {
                        if(MouseOnButton(x,y,listeBut[i])) {
                            listeBut[i].couleurTxt=color_jaune;
                            listeBut[i].couleurRect=color_black;
                            boutonSelected=i;
                        }
                        else {
                            listeBut[i].couleurTxt=color_red;
                            listeBut[i].couleurRect=color_grey_tr;
                        }
                    }
                }
                break;
        }

        // Dessin du jeu
        al_draw_scaled_bitmap(jeu, 0, 0, al_get_bitmap_width(jeu), al_get_bitmap_height(jeu), 0, 0, WIDTH, HEIGHT, 0);
        
        if(menu)
        {
            // Dessiner le rectangle de flou
            al_draw_filled_rectangle(0, 0, WIDTH, HEIGHT, al_map_rgba(0, 0, 0, 200));

            // Dessin de MENU
            al_draw_text(arial54, color_red, WIDTH/2, HEIGHT/5/2/2, ALLEGRO_ALIGN_CENTER, "MENU");
            
            // Dessin des boutons et rectangles
            for (i = 0; i < NBR_BOUT; ++i) {
                al_draw_filled_rectangle(listeBut[i].posX, listeBut[i].posY, listeBut[i].posX+listeBut[i].w, listeBut[i].posY+listeBut[i].h, listeBut[i].couleurRect);
                al_draw_text(listeBut[i].font, listeBut[i].couleurTxt, listeBut[i].posX+listeBut[i].w/2, listeBut[i].posY+listeBut[i].h/2-18, ALLEGRO_ALIGN_CENTER, listeBut[i].nom.c_str());
            }

        }

        // Rafraîchir
        al_flip_display();
    }

    // Clean up
    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);

    return 0;
}