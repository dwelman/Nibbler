#pragma once

#include "Entity.hpp"

class SnakeSegment : public Entity
{
public:
	enum SegmentDirection
	{
		NORTH = -1,
		SOUTH = 1,
		EAST = -2,
		WEST = 2
	};

	enum SnakeSegmentType
	{
		HEAD,
		BODY,
		TAIL
	};

    SnakeSegment(int x, int y);
	~SnakeSegment();
	SnakeSegment(SnakeSegment const &ss);

	SnakeSegment		&operator=(SnakeSegment const &ss);
	bool				operator==(SnakeSegment const &ss);
	SnakeSegmentType	GetSegmentType();
	void				SetSegmentType(SnakeSegmentType t);
	SegmentDirection	GetSegmentDirection();
	void				SetSegmentDirection(SegmentDirection d);
	void				Move();
    void                MoveBack();
    void                PrintInfo();
private:
	SnakeSegment();

    SnakeSegmentType type;
	SegmentDirection direction;
};