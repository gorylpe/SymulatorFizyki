#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Scena.h"
#include "Wektor.h"
#include "Obiekt.h"
#include "Kolo.h"
#include "Wielokat.h"
#include "Stale.h"
#include <iostream>


int main(int argc, char* argv[])
{
    srand(time(NULL));

    ALLEGRO_TIMER *physics_timer = NULL;
    ALLEGRO_DISPLAY *ekran = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue2 = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue3 = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue4 = NULL;
    ALLEGRO_FONT *czcionka = NULL;


    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_font_addon();
	al_init_ttf_addon();

    event_queue = al_create_event_queue();
    event_queue2 = al_create_event_queue();
    event_queue3 = al_create_event_queue();
    event_queue4 = al_create_event_queue();
    ekran = al_create_display(1024,600);
    physics_timer = al_create_timer(dt);
    czcionka = al_load_font("arial.ttf", 12, 0);

    al_register_event_source(event_queue, al_get_display_event_source(ekran));
    al_register_event_source(event_queue2, al_get_timer_event_source(physics_timer));
    al_register_event_source(event_queue3, al_get_keyboard_event_source());
    al_register_event_source(event_queue4, al_get_mouse_event_source());

    al_clear_to_color(al_map_rgb(255,255,255));

    al_start_timer(physics_timer);

    bool pojedynczaKlatka = true;

    Scena scena(dt, 10);

    Obiekt* obiekt;
    Kolo** kolo = new Kolo*[20];

    for(int i = 0; i < 14; ++i)
    {
        kolo[i] = new Kolo(Wektor(200 + i*30, 550-i*10), 10, 1, 0.5, 0.3, 255, 255, 255, 20);
    }
    for(int i = 14; i < 20; ++i)
    {
        kolo[i] = new Kolo(Wektor(620 + (i-14)*30, 410), 10, 1, 0.5, 0.3, 255, 255, 255, 20);
    }
    obiekt = new Obiekt(kolo[0]);
    for(int i = 1; i < 20; ++i)
    {
        obiekt->DodajKsztalt(kolo[i]);
    }
    scena.DodajObiekt(obiekt, TStatyczny);
    delete obiekt;
    for(int i = 0; i < 20; ++i)
    {
        delete kolo[i];
    }

    ALLEGRO_EVENT event;
    ALLEGRO_EVENT event2;
    ALLEGRO_EVENT event3;
    ALLEGRO_EVENT event4;

    while(true)
    {
        al_clear_to_color(al_map_rgb(0,0,0));
        al_get_next_event(event_queue, &event);
        al_get_next_event(event_queue2, &event2);
        al_get_next_event(event_queue3, &event3);
        al_get_next_event(event_queue4, &event4);
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;


        if(event4.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event4.mouse.button == 1)
        {
            event4.type = NULL;
            kolo[0] = new Kolo(Wektor(event4.mouse.x, event4.mouse.y), 20, 0.5, 0.5, 0.3, 255, 0, 0, 20);
            kolo[1] = new Kolo(Wektor(event4.mouse.x, event4.mouse.y + 20), 10, 0.5, 0.5, 0.3, 255, 0, 0, 20);
            obiekt = new Obiekt(kolo[0]);
            obiekt->DodajKsztalt(kolo[1]);
            scena.DodajObiekt(obiekt, TNormalny);
            delete obiekt;
            for(int i = 0; i < 2; ++i)
            {
                delete kolo[i];
            }
            /*kolo[0] = new Kolo(Wektor(event4.mouse.x, event4.mouse.y), 100, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[1] = new Kolo(Wektor(event4.mouse.x + 20, event4.mouse.y + 5), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[2] = new Kolo(Wektor(event4.mouse.x + 35, event4.mouse.y + 20), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[3] = new Kolo(Wektor(event4.mouse.x + 40, event4.mouse.y + 40), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[4] = new Kolo(Wektor(event4.mouse.x + 35, event4.mouse.y + 60), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[5] = new Kolo(Wektor(event4.mouse.x + 20, event4.mouse.y + 75), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[6] = new Kolo(Wektor(event4.mouse.x, event4.mouse.y + 80), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[7] = new Kolo(Wektor(event4.mouse.x - 20, event4.mouse.y + 75), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[8] = new Kolo(Wektor(event4.mouse.x - 35, event4.mouse.y + 60), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[9] = new Kolo(Wektor(event4.mouse.x - 40, event4.mouse.y + 40), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[10] = new Kolo(Wektor(event4.mouse.x - 35, event4.mouse.y + 20), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[11] = new Kolo(Wektor(event4.mouse.x - 20, event4.mouse.y + 5), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);

            obiekt = new Obiekt(kolo[0]);
            obiekt->predkosc = Wektor(0, 50);
            for(int i = 1; i < 12; ++i)
            {
                obiekt->DodajKsztalt(kolo[i]);
            }
            scena.DodajObiekt(obiekt, TNormalny);
            delete obiekt;
            for(int i = 0; i < 12; ++i)
            {
                delete kolo[i];
            }*/
        }

        if(event4.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event4.mouse.button == 2)
        {
            event4.type = NULL;
            kolo[0] = new Kolo(Wektor(event4.mouse.x, event4.mouse.y), 10, 0.3, 0.5, 0.3, 0, 255, 0, 20);
            kolo[1] = new Kolo(Wektor(event4.mouse.x, event4.mouse.y + 40), 10, 0.3, 0.5, 0.3, 0, 255, 0, 20);
            kolo[2] = new Kolo(Wektor(event4.mouse.x + 20, event4.mouse.y + 40), 10, 0.3, 0.5, 0.3, 0, 255, 0, 20);
            kolo[3] = new Kolo(Wektor(event4.mouse.x + 20, event4.mouse.y), 10, 0.3, 0.5, 0.3, 0, 255, 0, 20);
            obiekt = new Obiekt(kolo[0]);
            obiekt->DodajKsztalt(kolo[1]);
            obiekt->DodajKsztalt(kolo[2]);
            obiekt->DodajKsztalt(kolo[3]);
            scena.DodajObiekt(obiekt, TNormalny);
            delete obiekt;
            for(int i = 0; i < 4; ++i)
            {
                delete kolo[i];
            }
        }

        if(event4.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event4.mouse.button == 3)
        {
            event4.type = NULL;
            kolo[0] = new Kolo(Wektor(event4.mouse.x, event4.mouse.y), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[1] = new Kolo(Wektor(event4.mouse.x + 20, event4.mouse.y + 5), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[2] = new Kolo(Wektor(event4.mouse.x + 35, event4.mouse.y + 20), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[3] = new Kolo(Wektor(event4.mouse.x + 40, event4.mouse.y + 40), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[4] = new Kolo(Wektor(event4.mouse.x + 35, event4.mouse.y + 60), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[5] = new Kolo(Wektor(event4.mouse.x + 20, event4.mouse.y + 75), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[6] = new Kolo(Wektor(event4.mouse.x, event4.mouse.y + 80), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[7] = new Kolo(Wektor(event4.mouse.x - 20, event4.mouse.y + 75), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[8] = new Kolo(Wektor(event4.mouse.x - 35, event4.mouse.y + 60), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[9] = new Kolo(Wektor(event4.mouse.x - 40, event4.mouse.y + 40), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[10] = new Kolo(Wektor(event4.mouse.x - 35, event4.mouse.y + 20), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);
            kolo[11] = new Kolo(Wektor(event4.mouse.x - 20, event4.mouse.y + 5), 10, 0.5, 0.5, 0.3, 0, 0, 255, 15);

            obiekt = new Obiekt(kolo[0]);
            obiekt->predkosc = Wektor(0, 50);
            for(int i = 1; i < 12; ++i)
            {
                obiekt->DodajKsztalt(kolo[i]);
            }
            scena.DodajObiekt(obiekt, TNormalny);
            delete obiekt;
            for(int i = 0; i < 12; ++i)
            {
                delete kolo[i];
            }
        }

        if(event3.type == ALLEGRO_EVENT_KEY_DOWN && event3.keyboard.keycode == ALLEGRO_KEY_ENTER)
            pojedynczaKlatka = !pojedynczaKlatka;

        if(event2.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(event_queue2))
        {
            if(pojedynczaKlatka)
            {
                if(event3.type == ALLEGRO_EVENT_KEY_DOWN && event3.keyboard.keycode == ALLEGRO_KEY_SPACE)
                {
                    event3.type = NULL;
                    scena.Krok();
                }
                al_rest(0.006);
            }
            else
            {
                event2.type = NULL;
                scena.Krok();
            }
        }
        scena.Rysuj();
        al_draw_text(czcionka, al_map_rgb(128, 128, 255), 10, 10, 0, "Enter aby zatrzymac/wznowic symulacje.");
        al_draw_text(czcionka, al_map_rgb(128, 128, 255), 10, 30, 0, "Spacja przy zatrzymanym czasie aby przewinac symulacje o 1/100 s.");
        al_draw_text(czcionka, al_map_rgb(128, 128, 255), 10, 50, 0, "LPM by dodac kolo o promieniu 10, PPM 20.");

        al_flip_display();
    }
    al_flip_display();
    al_destroy_display(ekran);
}
