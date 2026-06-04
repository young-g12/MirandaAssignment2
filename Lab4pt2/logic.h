// Gilberto Miranda
class logic
{
public:

    // Reset the board
    void clear_board();

    // Return the shape at a location
    int get_shape(int row, int col);

    // Store a shape in the board
    void set_shape(int row, int col, int shape);

    // Randomly place pairs on the board
    void random_create();

    // Check if a card is revealed
    bool is_revealed(int row, int col);

    // Reveal a card
    void reveal(int row, int col);

    // Check if two cards match
    bool is_match(int row1, int col1, int row2, int col2);

    // Hide a card
    void hide(int row, int col);

    // Count the number of matched pairs
    int count_matches();

    bool is_matched(int row, int col);

    void set_matched(int row, int col);

private:
    int pattern[5][5];
    bool already_played[5][5];
    bool matched[5][5];
};