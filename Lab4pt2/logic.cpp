#include "logic.h"
#include <allegro5/allegro_primitives.h>
#include <cstdlib>
#include <ctime>

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

int logic::get_shape(int row, int col)
{
    return pattern[row][col];
}

void logic::set_shape(int row, int col, int shape)
{
    pattern[row][col] = shape;
}

void logic::random_create()
{
    int shapes[25];

    int index = 0;

    for (int i = 1; i <= 12; i++)
    {
        shapes[index++] = i;
        shapes[index++] = i;
    }

    shapes[24] = -1;

    for (int i = 24; i > 0; i--)
    {
        int r = rand() % (i + 1);

        int temp = shapes[i];
        shapes[i] = shapes[r];
        shapes[r] = temp;
    }

    index = 0;

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            pattern[row][col] = shapes[index++];
        }
    }
}

bool logic::is_revealed(int row, int col)
{
    return already_played[row][col];
}

void logic::reveal(int row, int col)
{
    already_played[row][col] = true;
}