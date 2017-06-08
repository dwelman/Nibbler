#pragma once

#include "Entity.hpp"

class Food : public Entity
{
public:
    Food(int _x, int _y, int _val, int _score);
	Food(Food const &f);
	~Food();

	Food	&operator=(Food const &f);

	int		getVal() const;
	void	setVal(int _val);
	int		getScore() const;
	void	setScore(int _score);
private:
    Food();

    int val;
	int score;
};