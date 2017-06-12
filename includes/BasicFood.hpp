#pragma once

#include "Food.hpp"

class BasicFood : public Food
{
public:
    BasicFood();
    BasicFood(int x, int y);
    ~BasicFood();

    BasicFood   *Clone(int x, int y) const;
private:
    BasicFood   &operator=(BasicFood const &f);
    BasicFood(BasicFood const &f);
};