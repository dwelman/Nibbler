#include "Food.hpp"

Food::Food(int _x, int _y, int _val, int _score, int _speedChange) : Entity(_x, _y), val(_val), score(_score), speedChange(_speedChange)
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
	this->speedChange = f.speedChange;
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

void Food::BeEaten(Snake &s) const
{
	s.ChangeScore(score);
	s.ChangeStomachSize(val);
	s.ChangeSpeed(speedChange);
}

void Food::SetCoords(int _x, int _y)
{
	this->x = _x;
	this->y = _y;
}

std::string Food::GetType() const
{
	return (type);
}
