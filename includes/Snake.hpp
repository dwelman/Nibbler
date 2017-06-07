#pragma once

#include <vector>
#include "SnakeSegment.hpp"

class Snake
{
public:
	Snake(int x, int y, SnakeSegment::SegmentDirection dir);
	Snake(Snake const &s);
	~Snake();

	Snake				&operator=(Snake const &s);
    void				ChangeSnakeHeadDirection(SnakeSegment::SegmentDirection dir);
    void				PrintSnake();
    void				UpdateSnake();
	void				Eat(int amount);
	void				Die();
	bool				IsDead();
	bool				CheckSelfCollision();
	std::vector<int>	GetAllX();
	std::vector<int>	GetAllY();
private:
	Snake();
	std::vector<SnakeSegment>	snake;
	int							stomachSize;
	bool						isDying;

	void						updateSnakeSegments();
	void						moveSnake();
	void						addPiece();
	void						removePiece();
	void						removePieceFromHead();
	void						digestFood();
};