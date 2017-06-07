#pragma once

#include "Entity.hpp"

class Food : public Entity
{
public:
    Food(int _x, int _y, int _val);
	Food(Food const &f);
	~Food();

	Food	&operator=(Food const &f);

	int		getVal();
	void	setVal(int _val);
private:
    Food();

    int val;
};