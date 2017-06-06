#include "SnakeSegment.hpp"

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
	x = x;
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
		y -= direction;
	}
	else
	{
		x -= direction;
	}
}
