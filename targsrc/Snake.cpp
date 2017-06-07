#include "Snake.hpp"

Snake::Snake(int x, int y, SnakeSegment::SegmentDirection dir)
{
	SnakeSegment newSegment(x, y);
	newSegment.SetSegmentType(SnakeSegment::HEAD);
	newSegment.SetSegmentDirection(dir);
	snake.push_back(newSegment);
	newSegment = SnakeSegment(x, y - 1);
	newSegment.SetSegmentDirection(dir);
	snake.push_back(newSegment);
	addPiece();
	addPiece();
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
	return (*this);
}

void Snake::ChangeSnakeHeadDirection(SnakeSegment::SegmentDirection dir)
{
	if (snake[0].GetSegmentDirection() == SnakeSegment::NORTH || snake[0].GetSegmentDirection() == SnakeSegment::SOUTH)
	{
		if (dir == SnakeSegment::EAST || dir == SnakeSegment::WEST)
		{
            snake[0].SetSegmentDirection(dir);
		}
	}
	else
	{
		if (dir == SnakeSegment::NORTH || dir == SnakeSegment::SOUTH)
		{
            snake[0].SetSegmentDirection(dir);
		}
	}
}

void Snake::updateSnakeSegments()
{
	for (std::size_t i = snake.size() - 1; i != 0; i--)
	{
		if (i > 0)
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

void Snake::addPiece()
{
	SnakeSegment newSegment(snake.back());
	newSegment.MoveBack();
	snake.back().SetSegmentType(SnakeSegment::BODY);
	snake.push_back(newSegment);
}

void Snake::PrintSnake()
{
    for (auto iter = snake.begin(); iter != snake.end(); iter++)
    {
        iter->PrintInfo();
    }
}

void Snake::UpdateSnake()
{
    moveSnake();
    updateSnakeSegments();
}
