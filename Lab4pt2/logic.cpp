#include "logic.h"
#include <allegro5/allegro_primitives.h>

void logic::clear_board()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            pattern[i][j] = -1;
            already_played[i][j] = false;
        }
    }
}