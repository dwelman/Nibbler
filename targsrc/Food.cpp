#include "Food.hpp"

Food::Food(int _x, int _y, int _val) : Entity(_x, _y), val(_val)
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
	return (*this);
}

int Food::getVal()
{
	return (val);
}

void Food::setVal(int _val)
{
	val = _val;
}
