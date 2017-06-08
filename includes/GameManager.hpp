#pragma once

#include <string>
#include "Snake.hpp"
#include "Food.hpp"

class GameManager
{
public:
	GameManager();
    ~GameManager();

    static GameManager &Instance();
	void			GiveSnake(Snake const &_snake);
	void			Update();
	Snake			*GetSnake();
private:
    GameManager(GameManager const &gm);
	GameManager &operator=(GameManager const &gm);

	Snake				*snake;
	int					mapWidth;
	int					mapHeight;
	int					foodCounter;
	std::vector<Food*>	food;

	void				spawnFood();
	void				checkFoodCollision();
	void				checkWallCollision();
};