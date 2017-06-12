#include "SuperFood.hpp"

SuperFood::SuperFood() : Food(0, 0, 5, 500, -15)
{
    type = "SUPER_FOOD";
}

SuperFood::SuperFood(int x, int y) : Food(x, y, 5, 500, -15)
{
    type = "SUPER_FOOD";
}

SuperFood::~SuperFood()
{

}

SuperFood   *SuperFood::Clone(int x, int y) const
{
    return (new SuperFood(x, y));
}