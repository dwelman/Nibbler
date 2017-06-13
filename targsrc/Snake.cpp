#include "Snake.hpp"

Snake::Snake(int pNum, int x, int y, SnakeSegment::SegmentDirection dir, int _speed, int _maxSpeed) : playerNum(pNum), stomachSize(0), isDying(false), score(0), speed(_speed), maxSpeed(_maxSpeed)
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
    canTurn = true;
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
	this->score = s.score;
    this->speed = s.speed;
	return (*this);
}

bool Snake::ChangeSnakeHeadDirection(SnakeSegment::SegmentDirection dir)
{
    if (canTurn)
    {
        if (snake[0].GetSegmentDirection() == SnakeSegment::NORTH || snake[0].GetSegmentDirection() == SnakeSegment::SOUTH)
        {
            if (dir == SnakeSegment::EAST || dir == SnakeSegment::WEST)
            {
                snake[0].SetSegmentDirection(dir);
                canTurn = false;
                return (true);
            }
        }
        else
        {
            if (dir == SnakeSegment::NORTH || dir == SnakeSegment::SOUTH)
            {
                snake[0].SetSegmentDirection(dir);
                canTurn = false;
                return (true);
            }
        }
    }
    return (false);
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
        if (CheckSelfCollision())
        {
            Die();
        }
		moveSnake();
		updateSnakeSegments();
		digestFood();
        canTurn = true;
	}
	else
	{
		removePieceFromHead();
	}
}

void Snake::Eat(Food const &f)
{
	f.BeEaten(*this);
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

std::vector<int> Snake::GetAllX()
{
	std::vector<int>	ret;
	for (auto iter = snake.begin(); iter != snake.end(); iter++)
	{
		ret.push_back(iter->getX());
	}
	return (ret);
}

std::vector<int> Snake::GetAllY()
{
	std::vector<int>	ret;
	for (auto iter = snake.begin(); iter != snake.end(); iter++)
	{
		ret.push_back(iter->getY());
	}
	return (ret);
}

SnakeSegment &Snake::GetHead()
{
	return (snake[0]);
}

int Snake::GetScore() const
{
	return (score);
}

void Snake::SetScore(int _score)
{
	score = _score;
}

std::vector<DrawableObj> Snake::GetSnakeDrawableObjects()
{
	std::vector<DrawableObj> ret;
	for (auto iter = snake.begin(); iter != snake.end(); iter++)
	{
		DrawableObj temp;
		temp.x = (*iter).getX();
		temp.y = (*iter).getY();
        if ((*iter).GetSegmentType() == SnakeSegment::HEAD)
        {
            temp.type = "HEAD";
        }
        else if ((*iter).GetSegmentType() == SnakeSegment::BODY)
        {
            temp.type = "BODY";
        }
        else
        {
            temp.type = "TAIL";
        }
        if ((*iter).GetSegmentDirection() == SnakeSegment::NORTH)
        {
            temp.dir = 'N';
        }
        else if ((*iter).GetSegmentDirection() == SnakeSegment::EAST)
        {
            temp.dir = 'E';
        }
        else if ((*iter).GetSegmentDirection() == SnakeSegment::SOUTH)
        {
            temp.dir = 'S';
        }
        else if ((*iter).GetSegmentDirection() == SnakeSegment::WEST)
        {
            temp.dir = 'W';
        }
		ret.push_back(temp);
	}
	return (ret);
}

void Snake::SetSpeed(int _speed)
{
    speed = _speed;
}

int Snake::GetSpeed() const
{
    return (speed);
}

void Snake::ChangeSpeed(int delta)
{
    speed += delta;
    if (speed < maxSpeed)
    {
        speed = maxSpeed;
    }
}

void Snake::ChangeScore(int delta)
{
    score += delta;
}

void Snake::ChangeStomachSize(int delta)
{
    stomachSize += delta;
}

int Snake::GetMaxSpeed() const
{
    return (maxSpeed);
}

int Snake::GetPlayerNumber() const
{
    return (playerNum);
}
