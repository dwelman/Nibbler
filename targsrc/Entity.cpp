#include "Entity.hpp"

Entity::Entity()
{
	x = 0;
	y = 0;
}

Entity::Entity(int _x, int _y) : x(_x), y(_y)
{
}

Entity::~Entity()
{
}

Entity::Entity(Entity const & e)
{
	*this = e;
}

Entity & Entity::operator=(Entity const & e)
{
	this->x = e.x;
	this->y = e.y;
	return (*this);
}

int Entity::getX()
{
	return (x);
}

void Entity::setX(int _x)
{
	x = _x;
}

int Entity::getY()
{
	return (y);
}

void Entity::setY(int _y)
{
	y = _y;
}
