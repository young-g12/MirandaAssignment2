
class logic
{
public:
    void clear_board();

    int get_shape(int row, int col);

    void set_shape(int row, int col, int shape);

private:
    int pattern[5][5];
    bool already_played[5][5];
};