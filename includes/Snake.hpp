#pragma once

#include <vector>
#include "SnakeSegment.hpp"

class Snake
{
public:
	Snake(int x, int y, SnakeSegment::SegmentDirection dir);
	Snake(Snake const &s);
	~Snake();

	Snake	&operator=(Snake const &s);
    void    ChangeSnakeHeadDirection(SnakeSegment::SegmentDirection dir);
    void    PrintSnake();
    void    UpdateSnake();
private:
	Snake();
	std::vector<SnakeSegment>	snake;

	void						updateSnakeSegments();
	void						moveSnake();
	void						addPiece();
};