#include "Snake.hpp"

Snake::Snake(int x, int y, SnakeSegment::SegmentDirection dir)
{
}

Snake::Snake(Snake const & s)
{
	*this = s;
}

Snake::~Snake()
{
}

Snake & Snake::operator=(Snake const & s)
{
	this->snake = s.snake;
	this->head = &snake[0];
	return (*this);
}

void Snake::updateSnakeSegments()
{
	for (std::size_t i = snake.size() - 1; i >= 0; i--)
	{
		if (i - 1 >= 0)
		{
			snake[i].SetSegmentDirection(snake[i - 1].GetSegmentDirection());
		}
	}
}

void Snake::moveSnake()
{
	auto end = snake.end();
	for (auto iter = snake.begin(); iter != end; iter++)
	{
		iter->Move();
	}
}
