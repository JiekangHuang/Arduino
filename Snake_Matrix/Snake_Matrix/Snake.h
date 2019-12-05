#include "node.h"

#define COL 24
#define ROW 16

#define FOOD 2
#define SKE 1
#define NON 0

typedef bool(*chk_f)(void);

class Snake
{
private:
	node snake_map[ROW][COL];
	uint8_t head_x, head_y;
	uint8_t food_x, food_y;
	int snake_len;
	uint8_t tail_x, tail_y;

	uint8_t startx, starty;

	bool is_dead();
	void swch(uint8_t&, uint8_t&);

public:
	Snake(uint8_t startx = 10, uint8_t starty = 8);
	~Snake();
	bool is_move(chk_f, int &speed);
	void Set_cur_dir(uint8_t);
	node* Get_snake_map();
	void Set_foodxy(uint8_t*, uint8_t*);
	void add_snake_len();
	void check_food(chk_f);

	uint8_t &Get_foodx();
	uint8_t &Get_foody();
};

Snake::Snake(uint8_t startx, uint8_t starty)
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			(*(snake_map + i) + j)->val = 0;
			(*(snake_map + i) + j)->dir = -1;
		}

	this->startx = startx;
	this->starty = starty;

	snake_len = 0;
	(*(snake_map + startx) + starty)->val = 1;
	tail_x = head_x = startx;
	tail_y = head_y = starty;

	food_x = food_y = NON;
	(*(snake_map + head_x) + head_y)->dir = 4;
}

Snake::~Snake()
{
}

bool Snake::is_dead()
{
	if (head_x >= ROW || head_x < 0 || head_y >= COL || head_y < 0 || (*(snake_map + head_x) + head_y)->val == SKE)
		return true;
	return false;
}

bool Snake::is_move(chk_f check_food, int &speed)
{
	node* cur_node = (*(snake_map + head_x) + head_y);
	switch (cur_node->dir)
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

	//check dead
	if (is_dead())
		return false;
	//check eat
	else if ((*(snake_map + head_x) + head_y)->val == FOOD)
	{
		speed -= 100;
		speed <= 150 ? speed = 150 : NULL;
		(*(snake_map + head_x) + head_y)->val = SKE;
		(*(snake_map + head_x) + head_y)->dir = cur_node->dir;
		check_food();
	}
	//move
	else
	{
		swch((*(snake_map + head_x) + head_y)->val, (*(snake_map + tail_x) + tail_y)->val);
		(*(snake_map + head_x) + head_y)->dir = cur_node->dir;

		node* pre_tail_node = (*(snake_map + tail_x) + tail_y);
		switch (pre_tail_node->dir)
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
		pre_tail_node->dir = -1;
	}
	return true;
}

void Snake::swch(uint8_t & a, uint8_t & b)
{
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

void Snake::Set_cur_dir(uint8_t dir)
{
	(*(snake_map + head_x) + head_y)->dir = dir;
}

inline node* Snake::Get_snake_map()
{
	return *(snake_map + 0);
}

inline void Snake::Set_foodxy(uint8_t *food_x, uint8_t *food_y)
{
	this->food_x = *food_x;
	this->food_y = *food_y;
}

inline void Snake::add_snake_len()
{
	this->snake_len++;
}

inline void Snake::check_food(chk_f check_food)
{
	if (check_food())
		this->add_snake_len();
}

uint8_t &Snake::Get_foodx()
{
	return this->food_x;
}
uint8_t &Snake::Get_foody()
{
	return this->food_y;
}