// Gilberto Miranda
// Memory Matching Game Logic

#include "logic.h"
#include <allegro5/allegro_primitives.h>
#include <cstdlib>
#include <ctime>

// Reset the board
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

// Return the shape at a location
int logic::get_shape(int row, int col)
{
    return pattern[row][col];
}

// Store a shape in the board
void logic::set_shape(int row, int col, int shape)
{
    pattern[row][col] = shape;
}

// Randomly place shape pairs on the board
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

    // Create 12 matching pairs
    for (int i = 24; i > 0; i--)
    {
        int r = rand() % (i + 1);

        int temp = shapes[i];
        shapes[i] = shapes[r];
        shapes[r] = temp;
    }

    index = 0;

    // Shuffle the shapes
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            pattern[row][col] = shapes[index++];
        }
    }
}

// Check if a card is revealed
bool logic::is_revealed(int row, int col)
{
    return already_played[row][col];
}

// Reveal a card
void logic::reveal(int row, int col)
{
    already_played[row][col] = true;
}

// Check if two cards match
bool logic::is_match(int row1, int col1, int row2, int col2)
{
    return pattern[row1][col1] == pattern[row2][col2];
}

// Hide a card
void logic::hide(int row, int col)
{
    already_played[row][col] = false;
}

// Count the number of matched pairs
int logic::count_matches()
{
    int revealedCount = 0;

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            if (already_played[row][col] &&
                pattern[row][col] != -1)
            {
                revealedCount++;
            }
        }
    }

    return revealedCount / 2;
}