class logic
{
public:
    void clear_board();

    int get_shape(int row, int col);

    void set_shape(int row, int col, int shape);

    void random_create();

    bool is_revealed(int row, int col);

    void reveal(int row, int col);

    bool is_match(int row1, int col1, int row2, int col2);

    void hide(int row, int col);

    int count_matches();

private:
    int pattern[5][5];
    bool already_played[5][5];
};