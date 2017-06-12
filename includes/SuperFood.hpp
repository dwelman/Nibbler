#pragma once

#include "Food.hpp"

class SuperFood : public Food
{
public:
    SuperFood();
    SuperFood(int x, int y);
    ~SuperFood();

    SuperFood   *Clone(int x, int y) const;
private:
    SuperFood   &operator=(SuperFood const &f);
    SuperFood(SuperFood const &f);
};