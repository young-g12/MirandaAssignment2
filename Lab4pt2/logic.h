
class logic
{
public:
    void setup();

    bool set_x(int x, int y);

    bool set_o(int x, int y);

    void done(bool& tie, bool& xwon, bool& owon);

    void draw_existing_moves();

private:
    char board[3][3];
};