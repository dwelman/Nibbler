#include "GameManager.hpp"
#include <vector>
#include <algorithm>
#include <stdlib.h>

GameManager::GameManager() : foodCounter(0), snake(nullptr)
{

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
	snake->UpdateSnake();
	checkFoodCollision();
	checkWallCollision();
	if (foodCounter == 0)
	{
		spawnFood();
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
	//Change this later to a food factory
	food.push_back(new Food(x, y, 1, 10));
	foodCounter++;
}

void GameManager::checkFoodCollision()
{
	for (auto iter = food.begin(); iter != food.end(); iter++)
	{
		Entity *temp = *iter;

		if (temp->getX() == snake->GetHead().getX() && temp->getY() == snake->GetHead().getY())
		{
			snake->Eat(**iter);
			food.erase(iter);
			--foodCounter;
		}
	}
}

void GameManager::checkWallCollision()
{
	int x = snake->GetHead().getX();
	int y = snake->GetHead().getY();
	if (x < 0 || y < 0 || x > mapWidth || y > mapHeight)
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
        ret.push_back(temp);
    }
    return (ret);
}
