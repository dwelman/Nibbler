#include "BasicFood.hpp"

BasicFood::BasicFood() : Food(0, 0, 1, 100, -1)
{
    type = "BASIC_FOOD";
}

BasicFood::BasicFood(int x, int y) : Food(x, y, 1, 100, -1)
{
    type = "BASIC_FOOD";
}

BasicFood::~BasicFood()
{

}

BasicFood   *BasicFood::Clone(int x, int y) const
{
    return (new BasicFood(x, y));
}