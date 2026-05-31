#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <ctime>
#include <cstdlib>
#include "logic.h"

void draw_board();

int main(void)
{
    logic game_logic;
   

    ALLEGRO_DISPLAY* Screen = NULL;
    int width = 640, height = 480;

    srand(time(NULL));

    if (!al_init())
    {
        al_show_native_message_box(NULL, "Error!", "Allegro has failed to initialize.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return (-1);
    }

    Screen = al_create_display(width, height);

    if (Screen == NULL)
    {
        al_show_native_message_box(Screen, "Error!", "Failed to create the display.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return (-1);
    }

    if (!al_install_mouse())
    {
        al_show_native_message_box(Screen, "Error!", "Failed to initialize the mouse!\n.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return (-1);
    }

    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    bool done = false;

    ALLEGRO_EVENT_QUEUE* event_queue = NULL;

    event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_display_event_source(Screen));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    game_logic.clear_board();

    while (!done)
    {
        ALLEGRO_EVENT ev;

        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (ev.mouse.button & 1)
            {
 
            }
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));

        draw_board();

       

 
  


        al_flip_display();
    }

    al_rest(5.0);

    al_destroy_event_queue(event_queue);
    al_destroy_display(Screen);

    return 0;
}


void draw_board()
{
    int startX = 50;
    int startY = 50;
    int cellSize = 80;

    for (int i = 0; i <= 5; i++)
    {
        al_draw_line(
            startX,
            startY + i * cellSize,
            startX + 5 * cellSize,
            startY + i * cellSize,
            al_map_rgb(255, 255, 255),
            2);
    }

    for (int i = 0; i <= 5; i++)
    {
        al_draw_line(
            startX + i * cellSize,
            startY,
            startX + i * cellSize,
            startY + 5 * cellSize,
            al_map_rgb(255, 255, 255),
            2);
    }
}



