#pragma once

#include "Entity.hpp"
#include "Snake.hpp"

class Snake;

class Food : public Entity
{
public:
    Food(int _x, int _y, int _val, int _score, int _speedChange);
	Food(Food const &f);
	~Food();

	Food	&operator=(Food const &f);

	int		getVal() const;
	void	setVal(int _val);
	int		getScore() const;
	void	setScore(int _score);
	void	BeEaten(Snake &s) const;
private:
    Food();

    int val;
	int score;
	int speedChange; //Positive is slower, negative is faster
};