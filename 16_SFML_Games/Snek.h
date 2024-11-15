#pragma once

enum Direction {
	SOUTH,
	WEST,
	EAST,
	NORTH
};

struct Vec2Int
{
	int x = 0;
	int y = 0;
};

const int GRID_HOR_MAX = 30;
const int GRID_VER_MAX = 20;

class Snek
{
public:
	Snek();
	~Snek();

	void MoveSnakeBody();
	void MoveSnakeHead();
	Vec2Int HeadTouchFruit(Vec2Int t_pos, int t_randA, int t_randB);
	void WrapSnakeOnScreenBounds();
	void CheckIfSnakeIntersects();

	int snakeLengthCurrent = 4;
	static const int SNAKE_LENGTH_MAX = 100;

	struct Segment
	{
		int segmentXpos = 0;
		int segmentYpos = 0;
	} snakeBody[SNAKE_LENGTH_MAX];

	Direction snakeDirection = Direction::SOUTH;

private:
	const int SNAKE_HEAD = 0;	
};



