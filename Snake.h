class node
{
public:
    char val;
    int dir;
    node()
    {
        val = non;
        dir = -1;
    }
};

class Snake
{
private:
    node map[24][32];
    int px, py;
    int x, y;
    int food_x, food_y;
    int snake_len;
    char direction;
    int sx_pop, sy_pop;

public:
    Snake();
    ~Snake();
    void check_food();
    void show();
    void key();
    bool is_del();
    bool is_move();
    void swch(char &, char &);
};

Snake::Snake()
{
    snake_len = 0;
    px = 10;
    py = 15;
    map[px][py].val = s;
    x = px;
    y = py;
    food_x = food_y = 0;
    direction = 'x';
    sx_pop = x;
    sy_pop = y;
    check_food();
}

Snake::~Snake()
{
}

//??????
void Snake::check_food()
{
    if (map[food_x][food_y].val != f)
    {
        srand(time(NULL));
        food_x = rand() % 23 + 0;
        food_y = rand() % 31 + 0;
        map[food_x][food_y].val = f;
        snake_len += 1;
    }
}

void Snake::show()
{
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            cout << map[i][j].val << " ";
        }
        cout << endl;
    }
    cout << "snake length = " << snake_len << endl;
    cout << "direction = " << direction << endl;
}

void Snake::key()
{
    char key = getch();
    switch (key)
    {
    case 'w': // UP
        direction = 'F';
        map[x][y].dir = 1;
        break;
    case 's': // DOWN
        direction = 'B';
        map[x][y].dir = 3;
        break;
    case 'd': // Right
        direction = 'R';
        map[x][y].dir = 4;
        break;
    case 'a': // Left
        direction = 'L';
        map[x][y].dir = 2;
        break;
    }
}

bool Snake::is_del()
{
    if (x >= 24 || x < 0 || y >= 32 || y < 0 || map[x][y].val == s)
        return true;
    return false;
}

bool Snake::is_move()
{
    node &cur = map[x][y];
    switch (cur.dir)
    {
    case 1:
        x -= 1;
        break;
    case 3:
        x += 1;
        break;
    case 4:
        y += 1;
        break;
    case 2:
        y -= 1;
        break;
    }

    //check eat
    if (map[x][y].val == f)
    {
        map[x][y].val = s;
        map[x][y].dir = cur.dir;
        return true;
    }

    if (is_del())
        return false;
    swch(map[x][y].val, map[sx_pop][sy_pop].val);
    map[x][y].dir = cur.dir;

    node &pre_pop = map[sx_pop][sy_pop];
    switch (pre_pop.dir)
    {
    case 1:
        sx_pop -= 1;
        break;
    case 3:
        sx_pop += 1;
        break;
    case 4:
        sy_pop += 1;
        break;
    case 2:
        sy_pop -= 1;
        break;
    }
    pre_pop.dir = -1;
    return true;
}

void Snake::swch(char &a, char &b)
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

int main(void)
{
    Snake snake;
    //start
    snake.show();
    while (true)
    {
        snake.key();
        if (!snake.is_move())
            break;
        snake.check_food();
        system("cls");
        snake.show();
    }

    system("cls");
    cout << "GAME OVER !!" << endl;
    system("pause");
    return 0;
}

//?? Snake struct?member:value?direction
//Snack length > 1 ???????????