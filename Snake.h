class node
{
public:
    bool val;
    byte dir;
    node()
    {
        val = 0;
        dir = -1;
    }
};

class Snake
{
private:
    node snake_map[24][32];
    int px, py;
    int head_x, head_y;
    int food_x, food_y;
    int snake_len;
    char direction;
    int tail_x, tail_y;

    bool is_del();
    void swch(char &, char &);
    void check_food();

public:
    Snake();
    ~Snake();
    bool is_move();
    void Set_cur_dir(byte);
};

Snake::Snake()
{
    snake_len = 0;
    //px為暫時的預設開始位置
    px = 10;
    py = 15;
    snake_map[px][py].val = s;
    head_x = px;
    head_y = py;
    food_x = food_y = 0;
    tail_x = head_x;
    tail_y = head_y;
    check_food();
}

Snake::~Snake()
{
}

void Snake::check_food()
{
    if (snake_map[food_x][food_y].val != f)
    {
        srand(time(NULL));
        food_x = rand() % 23 + 0;
        food_y = rand() % 31 + 0;
        snake_map[food_x][food_y].val = f;
        snake_len += 1;
    }
}

bool Snake::is_del()
{
    if (head_x >= 24 || head_x < 0 || head_y >= 32 || head_y < 0 || snake_map[head_x][head_y].val == true)
        return true;
    return false;
}

bool Snake::is_move()
{
    node &cur = snake_map[head_x][head_y];
    switch (cur.dir)
    {
    case 1:
        head_x -= 1;
        break;
    case 2:
        head_y -= 1;
        break;
    case 3:
        head_x += 1;
        break;
    case 4:
        head_y += 1;
        break;
    }

    //check eat
    if (snake_map[head_x][head_y].val == f)
    {
        snake_map[head_x][head_y].val = s;
        snake_map[head_x][head_y].dir = cur.dir;
        return true;
    }

    if (is_del())
        return false;
    swch(snake_map[head_x][head_y].val, snake_map[tail_x][tail_y].val);
    snake_map[head_x][head_y].dir = cur.dir;

    node &pre_tail = snake_map[tail_x][tail_y];
    switch (pre_tail.dir)
    {
    case 1:
        tail_x -= 1;
        break;
    case 3:
        tail_x += 1;
        break;
    case 4:
        tail_y += 1;
        break;
    case 2:
        tail_y -= 1;
        break;
    }
    pre_tail.dir = -1;
    return true;
}

void Snake::swch(char &a, char &b)
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

void Snake::Set_cur_dir(byte dir)
{
    snake_map[head_x][head_y].dir() = dir;
}
