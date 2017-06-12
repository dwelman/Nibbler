#include "GameManager.hpp"
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include "BasicFood.hpp"
#include "ShrinkFood.hpp"
#include "SuperFood.hpp"

GameManager::GameManager() : foodCounter(0), snake(nullptr)
{
	updateTick = SDL_GetTicks();
    factory.LearnFood(new BasicFood());
    factory.LearnFood(new ShrinkFood());
    factory.LearnFood(new SuperFood());
}

GameManager::~GameManager()
{
	delete snake;
}

GameManager & GameManager::Instance()
{
	//For singleton pattern
	static GameManager instance;
	return (instance);
}

void GameManager::GiveSnake(Snake const & _snake)
{
	snake = new Snake(_snake);
}

void GameManager::Update()
{
	if (SDL_GetTicks() - updateTick > snake->GetSpeed())
    {
        if (foodCounter == 0)
        {
            spawnFood();
        }
        snake->UpdateSnake();
        checkFoodCollision();
        checkWallCollision();
        updateTick = SDL_GetTicks();
    }
}

Snake *GameManager::GetSnake()
{
	return (snake);
}

void GameManager::spawnFood()
{
	std::vector<int> xCoords = snake->GetAllX();
	std::vector<int> yCoords = snake->GetAllY();
	int	x = 0;
	int y = 0;
	do
	{
		x = rand() % mapWidth;
		y = rand() % mapHeight;
	}
	while (std::find(xCoords.begin(), xCoords.end(), x) != xCoords.end() && std::find(yCoords.begin(), yCoords.end(), y) != yCoords.end());
    if (rand() % 100 >= 20)
    {
        food.push_back(factory.CreateFood("BASIC_FOOD", x, y));
    }
    else
    {
        if (rand() % 100 >= 30)
        {
            food.push_back(factory.CreateFood("SHRINK_FOOD", x, y));
        }
        else
        {
            food.push_back(factory.CreateFood("SUPER_FOOD", x, y));
        }
    }
	foodCounter++;
}

void GameManager::checkFoodCollision()
{
    std::vector<int>    toRemove;
	for (int i = 0; i < food.size(); i++)
	{
		Entity *temp = food[i];
        if (temp != NULL)
        {
            if (temp->getX() == snake->GetHead().getX() && temp->getY() == snake->GetHead().getY()) {
                snake->Eat(*food[i]);
                toRemove.push_back(i);
            }
        }
	}
    for (int i = 0; i < toRemove.size(); i++)
    {
        food.erase(food.begin() + toRemove[i]);
        --foodCounter;
    }
}

void GameManager::checkWallCollision()
{
	int x = snake->GetHead().getX();
	int y = snake->GetHead().getY();
	if (x < 0 || y < 0 || x >= mapWidth || y >= mapHeight)
	{
		snake->Die();
	}
}

std::vector<DrawableObj> GameManager::GetDrawableObjects()
{
    std::vector<DrawableObj> ret;
    for (auto iter = food.begin(); iter != food.end(); iter++)
    {
        DrawableObj temp;
        temp.x = (*iter)->getX();
        temp.y = (*iter)->getY();
        temp.type = (*iter)->GetType();
        ret.push_back(temp);
    }
    auto snakeTemp = snake->GetSnakeDrawableObjects();
    ret.insert(ret.end(), snakeTemp.begin(), snakeTemp.end());
    return (ret);
}

void GameManager::SetMapWidth(int width)
{
    mapWidth = width;
}

void GameManager::SetMapHeight(int height)
{
    mapHeight = height;
}
