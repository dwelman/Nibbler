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
private:
	Snake();
	std::vector<SnakeSegment>	snake;
	SnakeSegment				*head;

	void						updateSnakeSegments();
	void						moveSnake();
};