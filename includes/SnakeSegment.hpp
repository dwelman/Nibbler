#pragma once

class SnakeSegment
{
public:
	enum SegmentDirection
	{
		NORTH = 1,
		SOUTH = -1,
		EAST = -1,
		WEST = 1
	};

	enum SnakeSegmentType
	{
		HEAD,
		BODY,
		TAIL
	};

	SnakeSegment();
	~SnakeSegment();
	SnakeSegment(SnakeSegment const &ss);

	SnakeSegment		&operator=(SnakeSegment const &ss);
	int					GetX();
	void				SetX(int _x);
	int					GetY();
	void				SetY(int _y);
	SnakeSegmentType	GetSegmentType();
	void				SetSegmentType(SnakeSegmentType t);
	SegmentDirection	GetSegmentDirection();
	void				SetSegmentDirection(SegmentDirection d);
	void				Move();
private:
	int				 x;
	int				 y;
    SnakeSegmentType type;
	SegmentDirection direction;
};