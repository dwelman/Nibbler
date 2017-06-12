#pragma once

#include "Food.hpp"
#include <vector>

class FoodFactory
{
public:
    FoodFactory();
    FoodFactory(FoodFactory const &ff);
    ~FoodFactory();

    FoodFactory &operator=(FoodFactory const &ff);
    void    LearnFood(Food *f);
    Food    *CreateFood(std::string type, int x, int y);
private:
    std::vector<Food*>  inv;
};