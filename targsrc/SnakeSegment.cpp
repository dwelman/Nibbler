#include "SnakeSegment.hpp"
#include <iostream>

SnakeSegment::SnakeSegment()
{
	x = 0;
	y = 0;
	type = BODY;
	direction = NORTH;
}

SnakeSegment::~SnakeSegment()
{
}

SnakeSegment::SnakeSegment(SnakeSegment const & ss)
{
	*this = ss;
}

SnakeSegment & SnakeSegment::operator=(SnakeSegment const & ss)
{
	this->direction = ss.direction;
	this->type = ss.type;
	this->x = ss.x;
	this->y = ss.y;
	return (*this);
}

int SnakeSegment::GetX()
{
	return (x);
}

void SnakeSegment::SetX(int _x)
{
	x = _x;
}

int SnakeSegment::GetY()
{
	return (y);
}

void SnakeSegment::SetY(int _y)
{
	y = _y;
}

SnakeSegment::SnakeSegmentType SnakeSegment::GetSegmentType()
{
	return (type);
}

void SnakeSegment::SetSegmentType(SnakeSegmentType t)
{
	type = t;
}

SnakeSegment::SegmentDirection SnakeSegment::GetSegmentDirection()
{
	return (direction);
}

void SnakeSegment::SetSegmentDirection(SegmentDirection d)
{
	direction = d;
}

void SnakeSegment::Move()
{
    if (direction == NORTH || direction == SOUTH)
    {
        y += direction;
    }
    else
    {
        if (direction == EAST)
        {
            x -= 1;
        }
        else
        {
            x += 1;
        }
    }
}

SnakeSegment::SnakeSegment(int _x, int _y)
{
	x = _x;
	y = _y;
	type = BODY;
	direction = NORTH;
}

void SnakeSegment::MoveBack()
{
    if (direction == NORTH || direction == SOUTH)
    {
        y -= direction;
    }
    else
    {
        if (direction == EAST)
        {
            x += 1;
        }
        else
        {
            x -= 1;
        }
    }
}

void SnakeSegment::PrintInfo()
{
	std::cout << "X :" << x << " Y: " << y;
    if (type == HEAD)
    {
        std::cout << " HEAD ";
    }
    else if (type == BODY)
    {
        std::cout << " BODY ";
    }
    else
    {
        std::cout << " TAIL ";
    }

	if (direction == NORTH)
	{
        std::cout << " N ";
	}
	else if (direction == SOUTH)
	{
        std::cout << " S ";
	}
	else if (direction == EAST)
	{
        std::cout << " E ";
	}
    else
    {
        std::cout << " W ";
    }
	std::cout << std::endl;
}
