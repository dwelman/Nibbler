#include "FoodFactory.hpp"

FoodFactory::FoodFactory()
{

}

FoodFactory::FoodFactory(FoodFactory const &ff)
{
    *this = ff;
}

FoodFactory::~FoodFactory()
{

}

FoodFactory &FoodFactory::operator=(FoodFactory const &ff)
{
    this->inv = ff.inv;
    return (*this);
}

void    FoodFactory::LearnFood(Food *f)
{
    inv.push_back(f);
}

Food    *FoodFactory::CreateFood(std::string type, int x, int y)
{
    for (auto iter = inv.begin(); iter != inv.end(); iter++)
    {
        if ((*iter)->GetType() == type)
        {
            return ((*iter)->Clone(x, y));
        }
    }
    return (nullptr);
}