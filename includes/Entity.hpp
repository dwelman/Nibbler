#pragma once

class Entity
{
public:
	Entity();
	Entity(int _x, int _y);
	~Entity();
	Entity(Entity const &e);

	Entity	&operator=(Entity const &e);
	bool	operator==(Entity const &e);

	int		getX();
	void	setX(int _x);
	int		getY();
	void	setY(int _y);
protected:
	int x;
	int y;
};