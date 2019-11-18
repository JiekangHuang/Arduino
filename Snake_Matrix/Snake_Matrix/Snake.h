#include "node.h"

#define COL 24
#define ROW 24

#define FOOD 2
#define SKE 1
#define NON 0
#define STARTX 10
#define STARTY 8

class Snake
{
private:
	node* snake_map[24];
	int head_x, head_y;
	int food_x, food_y;
	int snake_len;
	int tail_x, tail_y;

	bool is_del();
	void swch(byte&, byte&);
	void check_food();

public:
	Snake();
	~Snake();
	bool is_move();
	void Set_cur_dir(byte);
	node** Get_snake_map();
};

Snake::Snake()
{
	randomSeed(analogRead(A0));

	snake_len = 0;
	snake_map[STARTX][STARTY].val = 1;
	tail_x = head_x = STARTX;
	tail_y = head_y = STARTY;

	food_x = food_y = NON;
	check_food();
}

Snake::~Snake()
{
}

void Snake::check_food()
{
	if (snake_map[food_x][food_y].val != FOOD)
	{
		food_x = random(16);
		food_y = random(24);
		snake_map[food_x][food_y].val = FOOD;
		snake_len += 1;
	}
}

bool Snake::is_del()
{
	if (head_x >= ROW || head_x < 0 || head_y >= COL || head_y < 0 || snake_map[head_x][head_y].val == SKE)
		return true;
	return false;
}

bool Snake::is_move()
{
	node& cur_node = snake_map[head_x][head_y];
	switch (cur_node.dir)
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

	//check del
	if (is_del())
		return false;
	//check eat
	else if (snake_map[head_x][head_y].val == FOOD)
	{
		snake_map[head_x][head_y].val = SKE;
		snake_map[head_x][head_y].dir = cur_node.dir;
		check_food();
	}
	//move
	else
	{
		swch(snake_map[head_x][head_y].val, snake_map[tail_x][tail_y].val);
		snake_map[head_x][head_y].dir = cur_node.dir;

		node& pre_tail_node = snake_map[tail_x][tail_y];
		switch (pre_tail_node.dir)
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
		pre_tail_node.dir = -1;
	}
	return true;
}

void Snake::swch(byte & a, byte & b)
{
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

void Snake::Set_cur_dir(byte dir)
{
	snake_map[head_x][head_y].dir = dir;
}

inline node** Snake::Get_snake_map()
{
	return this->snake_map;
}
