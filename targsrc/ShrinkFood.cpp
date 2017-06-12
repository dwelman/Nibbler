#include "ShrinkFood.hpp"

ShrinkFood::ShrinkFood() : Food(0, 0, -1, 80, 1)
{
    type = "SHRINK_FOOD";
}

ShrinkFood::ShrinkFood(int x, int y) : Food(x, y, -1, 80, 1)
{
    type = "SHRINK_FOOD";
}

ShrinkFood::~ShrinkFood()
{

}

ShrinkFood   *ShrinkFood::Clone(int x, int y) const
{
    return (new ShrinkFood(x, y));
}