#include "GameManager.hpp"
#include <vector>
#include <algorithm>

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
	food.push_back(new Food(x, y, 1));
	foodCounter++;
}
