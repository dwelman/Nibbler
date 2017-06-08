#include "Food.hpp"

Food::Food(int _x, int _y, int _val, int _score) : Entity(_x, _y), val(_val), score(_score)
{
}

Food::Food(Food const & f)
{
	*this = f;
}

Food::~Food()
{
}

Food & Food::operator=(Food const & f)
{
	Entity::operator=(f);
	this->val = f.val;
	this->score = f.score;
	return (*this);
}

int Food::getVal() const
{
	return (val);
}

void Food::setVal(int _val)
{
	val = _val;
}

int Food::getScore() const
{
	return (score);
}

void Food::setScore(int _score)
{
	score = _score;
}
