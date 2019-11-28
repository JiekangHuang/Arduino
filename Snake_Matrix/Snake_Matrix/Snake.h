#include "node.h"
#include "Arduino.h"

#define COL 24
#define ROW 16

#define FOOD 2
#define SKE 1
#define NON 0

class Snake
{
private:
	node snake_map[ROW][COL];
	uint8_t head_x, head_y;
	uint8_t food_x, food_y;
	int snake_len;
	uint8_t tail_x, tail_y;

	uint8_t startx, starty;

	bool is_del();
	void swch(uint8_t&, uint8_t&);
	void check_food();

public:
	Snake(uint8_t startx = 10, uint8_t starty = 8);
	~Snake();
	bool is_move();
	void Set_cur_dir(uint8_t);
	node* Get_snake_map();
	void init()
	{
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 24; j++)
				Serial.print((*(snake_map + i) + j)->val);
			Serial.println();
		}
		Serial.println();
	}
};

Snake::Snake(uint8_t startx, uint8_t starty)
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			(*(snake_map + i) + j)->val = 0;

	this->startx = startx;
	this->starty = starty;
	randomSeed(analogRead(0));

	snake_len = 0;
	(*(snake_map + startx) + starty)->val = 1;
	tail_x = head_x = startx;
	tail_y = head_y = starty;

	food_x = food_y = NON;
	Serial.begin(115200);
	check_food();
}

Snake::~Snake()
{
}

void Snake::check_food()
{
	if ((*(snake_map + food_x) + food_y)->val != FOOD)
	{
		(*(snake_map + food_x) + food_y)->val = FOOD;
		snake_len += 1;
		long a = random(16);
		Serial.println("test");
	}
}

bool Snake::is_del()
{
	if (head_x >= ROW || head_x < 0 || head_y >= COL || head_y < 0 || (*(snake_map + head_x) + head_y)->val == SKE)
		return true;
	return false;
}

bool Snake::is_move()
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
	if (is_del())
		return false;
	//check eat
	else if ((*(snake_map + head_x) + head_y)->val == FOOD)
	{
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
	return snake_map[0];
}
