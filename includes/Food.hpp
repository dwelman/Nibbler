#pragma once

#include "Entity.hpp"
#include "Snake.hpp"
#include <string>

class Snake;

class Food : public Entity
{
public:
	Food();
    Food(int _x, int _y, int _val, int _score, int _speedChange);
	Food(Food const &f);
	~Food();

	Food	&operator=(Food const &f);

	int			getVal() const;
	void		setVal(int _val);
	int			getScore() const;
	void		setScore(int _score);
	void 		SetCoords(int _x, int _y);
	std::string	GetType() const;
	void		BeEaten(Snake &s) const;

	virtual Food	*Clone(int x, int y) const = 0;
protected:

    int 		val;
	int 		score;
	int 		speedChange; //Positive is slower, negative is faster
	std::string	type;
};