#pragma once

#include <string>
#include "Snake.hpp"
#include "Food.hpp"
#include "nibbler.hpp"
#include "FoodFactory.hpp"

class GameManager
{
public:
	GameManager();
    ~GameManager();

    static GameManager          &Instance();
	void			            GiveSnake(Snake const &_snake);
	void			            Update();
	Snake			            *GetSnake();
    std::vector<DrawableObj>    GetDrawableObjects();
    void                        SetMapWidth(int width);
    void                        SetMapHeight(int height);
    int							GetMapWidth();
	int							GetMapHeight();

	int 						highScore;
private:
    GameManager(GameManager const &gm);
	GameManager &operator=(GameManager const &gm);

	Snake				*snake;
	int					mapWidth;
	int					mapHeight;
	int					foodCounter;
	std::vector<Food*>	food;
	Uint32	 			updateTick;
	FoodFactory			factory;

	void				spawnFood();
	void				checkFoodCollision();
	void				checkWallCollision();
};