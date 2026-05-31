#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <ctime>
#include <cstdlib>
#include "logic.h"

void draw_board();
void draw_shape(int shape, int x, int y);
void draw_all_shapes(logic& game_logic);

void draw_circle_shape(int x, int y);
void draw_rectangle_shape(int x, int y);
void draw_triangle_shape(int x, int y);
void draw_diamond_shape(int x, int y);
void draw_oval_shape(int x, int y);

void draw_status(logic& game_logic);

int main(void)
{
    logic game_logic;
    int mouseX = 0;
    int mouseY = 0;
   
    bool firstCardSelected = false;

    int firstRow = -1;
    int firstCol = -1;

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
    game_logic.random_create();

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
            mouseX = ev.mouse.x;
            mouseY = ev.mouse.y;

            int startX = 50;
            int startY = 50;
            int cellSize = 80;

            if (mouseX >= startX &&
                mouseX < startX + 5 * cellSize &&
                mouseY >= startY &&
                mouseY < startY + 5 * cellSize)
            {
                int col = (mouseX - startX) / cellSize;
                int row = (mouseY - startY) / cellSize;

                if (!game_logic.is_revealed(row, col))
                {
                    game_logic.reveal(row, col);

                    if (!firstCardSelected)
                    {
                        firstCardSelected = true;

                        firstRow = row;
                        firstCol = col;
                    }
                    else
                    {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        draw_board();
                        draw_all_shapes(game_logic);
                        al_flip_display();

                        al_rest(5.0);

                        if (!game_logic.is_match(
                            firstRow,
                            firstCol,
                            row,
                            col))
                        {
                            game_logic.hide(firstRow, firstCol);
                            game_logic.hide(row, col);
                        }

                        firstCardSelected = false;
                    }
                }
            }
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));

        draw_board();
        draw_all_shapes(game_logic);
        draw_status(game_logic);
       
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

void draw_circle_shape(int x, int y)
{
    al_draw_circle(x, y, 25,
        al_map_rgb(255, 255, 0), 3);
}

void draw_rectangle_shape(int x, int y)
{
    al_draw_rectangle(
        x - 25,
        y - 25,
        x + 25,
        y + 25,
        al_map_rgb(0, 255, 0),
        3);
}

void draw_triangle_shape(int x, int y)
{
    al_draw_triangle(
        x,
        y - 30,
        x - 25,
        y + 25,
        x + 25,
        y + 25,
        al_map_rgb(255, 0, 0),
        3);
}

void draw_diamond_shape(int x, int y)
{
    al_draw_line(x, y - 30, x + 30, y,
        al_map_rgb(0, 255, 255), 3);

    al_draw_line(x + 30, y, x, y + 30,
        al_map_rgb(0, 255, 255), 3);

    al_draw_line(x, y + 30, x - 30, y,
        al_map_rgb(0, 255, 255), 3);

    al_draw_line(x - 30, y, x, y - 30,
        al_map_rgb(0, 255, 255), 3);
}

void draw_oval_shape(int x, int y)
{
    al_draw_ellipse(
        x,
        y,
        35,
        20,
        al_map_rgb(255, 0, 255),
        3);
}

void draw_shape(int shape, int x, int y)
{
    switch (shape % 5)
    {
    case 0:
        draw_circle_shape(x, y);
        break;

    case 1:
        draw_rectangle_shape(x, y);
        break;

    case 2:
        draw_triangle_shape(x, y);
        break;

    case 3:
        draw_diamond_shape(x, y);
        break;

    case 4:
        draw_oval_shape(x, y);
        break;
    }
}

void draw_all_shapes(logic& game_logic)
{
    int startX = 50;
    int startY = 50;
    int cellSize = 80;

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            int shape = game_logic.get_shape(row, col);

            if (shape != -1 &&
                game_logic.is_revealed(row, col))
            {
                int centerX = startX + col * cellSize + cellSize / 2;
                int centerY = startY + row * cellSize + cellSize / 2;

                draw_shape(shape, centerX, centerY);
            }
        }
    }
}

void draw_status(logic& game_logic)
{
    ALLEGRO_FONT* font =
        al_create_builtin_font();

    int matches = game_logic.count_matches();

    int remaining = 12 - matches;

    al_draw_textf(
        font,
        al_map_rgb(255, 255, 255),
        470,
        60,
        0,
        "Pairs Found: %d",
        matches);

    al_draw_textf(
        font,
        al_map_rgb(255, 255, 255),
        470,
        90,
        0,
        "Remaining: %d",
        remaining);

    if (matches == 12)
    {
        al_draw_text(
            font,
            al_map_rgb(0, 255, 0),
            470,
            140,
            0,
            "YOU WIN!");
    }
}