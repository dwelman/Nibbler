#pragma once

#include "Food.hpp"

class ShrinkFood : public Food
{
public:
    ShrinkFood();
    ShrinkFood(int x, int y);
    ~ShrinkFood();

    ShrinkFood   *Clone(int x, int y) const;
private:
    ShrinkFood   &operator=(ShrinkFood const &f);
    ShrinkFood(ShrinkFood const &f);
};