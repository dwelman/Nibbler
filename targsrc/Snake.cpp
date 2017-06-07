#include "Snake.hpp"

Snake::Snake(int x, int y, SnakeSegment::SegmentDirection dir) : stomachSize(0), isDying(false)
{
	SnakeSegment newSegment(x, y);
	newSegment.SetSegmentType(SnakeSegment::HEAD);
	newSegment.SetSegmentDirection(dir);
	snake.push_back(newSegment);
	newSegment = SnakeSegment(newSegment);
	newSegment.SetSegmentType(SnakeSegment::BODY);
	newSegment.SetSegmentDirection(dir);
	newSegment.MoveBack();
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
	this->isDying = s.isDying;
	this->stomachSize = s.stomachSize;
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
	newSegment.SetSegmentType(SnakeSegment::TAIL);
	snake.push_back(newSegment);
}

void Snake::removePiece()
{
	if (snake.size() > 2)
	{
		snake.pop_back();
		snake.back().SetSegmentType(SnakeSegment::TAIL);
	}
}

void Snake::removePieceFromHead()
{
	if (snake.size() > 0)
	{
		snake.erase(snake.begin(), snake.begin() + 1);
	}
}

void Snake::digestFood()
{
	if (stomachSize > 0)
	{
		addPiece();
		stomachSize--;
	}
	else if (stomachSize < 0)
	{
		removePiece();
		stomachSize++;
	}
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
	if (!isDying)
	{
		moveSnake();
		updateSnakeSegments();
		digestFood();
	}
	else
	{
		removePieceFromHead();
	}
}

void Snake::Eat(int amount)
{
	stomachSize += amount;
}

void Snake::Die()
{
	isDying = true;
}

bool Snake::IsDead()
{
	if (snake.size() == 0)
	{
		return (true);
	}
	return (false);
}

bool Snake::CheckSelfCollision()
{
	SnakeSegment &head = snake[0];
	for (auto iter = snake.begin() + 1; iter != snake.end(); iter++)
	{
		if (head == *iter)
		{
			return (true);
		}
	}
	return (false);
}

std::vector<int> Snake::getAllX()
{
	std::vector<int>	ret;
	for (auto iter = snake.begin(); iter != snake.end(); iter++)
	{
		ret.push_back(iter->getX());
	}
	return (ret);
}

std::vector<int> Snake::getAllY()
{
	std::vector<int>	ret;
	for (auto iter = snake.begin(); iter != snake.end(); iter++)
	{
		ret.push_back(iter->getY());
	}
	return (ret);
}
