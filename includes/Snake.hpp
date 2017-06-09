#pragma once

#include <vector>
#include "SnakeSegment.hpp"
#include "Food.hpp"
#include "nibbler.hpp"

class Food;

class Snake
{
public:
	Snake(int x, int y, SnakeSegment::SegmentDirection dir, int _speed);
	Snake(Snake const &s);
	~Snake();

	Snake				        &operator=(Snake const &s);
    bool				        ChangeSnakeHeadDirection(SnakeSegment::SegmentDirection dir);
    void				        PrintSnake();
    void				        UpdateSnake();
	void				        Eat(Food const &f);
	void				        Die();
	bool				        IsDead();
	bool				        CheckSelfCollision();
	std::vector<int>	        GetAllX();
	std::vector<int>	        GetAllY();
	SnakeSegment		        &GetHead();
	int					        GetScore() const;
	void				        SetScore(int _score);
    void                        ChangeScore(int delta);
    std::vector<DrawableObj>    GetSnakeDrawableObjects();
    int                         GetSpeed() const;
    void                        SetSpeed(int _speed);
    void                        ChangeSpeed(int delta);
    void                        ChangeStomachSize(int delta);
private:
	Snake();
	std::vector<SnakeSegment>	snake;
	int							stomachSize;
	bool						isDying;
	int							score;
    int                         speed;
    int                         maxSpeed;

	void						updateSnakeSegments();
	void						moveSnake();
	void						addPiece();
	void						removePiece();
	void						removePieceFromHead();
	void						digestFood();
};