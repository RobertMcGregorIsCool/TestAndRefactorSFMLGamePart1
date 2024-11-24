#include "pch.h"

#include"../16_SFML_Games/Snek.h"

TEST(Snek, HeadIsTouchingFruit) {
	Snek snek;

	Vec2Int startVec = { 0, 0 };
	Vec2Int testVec = { 9, 4 };
	EXPECT_EQ(testVec.x, snek.HeadTouchFruit(startVec, testVec.x, testVec.y).x);
	EXPECT_EQ(testVec.y, snek.HeadTouchFruit(startVec, testVec.x, testVec.y).y);
}

TEST(Snek, SnakeBodyMoves) {
	Snek snek;

	snek.snakeBody[0].segmentYpos = 1;
	snek.snakeBody[0].segmentXpos = 9;

	snek.MoveSnakeBody();

	EXPECT_EQ(snek.snakeBody[0].segmentYpos, snek.snakeBody[1].segmentYpos);
	EXPECT_EQ(snek.snakeBody[0].segmentXpos, snek.snakeBody[1].segmentXpos);
}

TEST(Snek, HeadMovesInSnakeDirection) {
	Snek snek;

	snek.snakeDirection = WEST;
	snek.MoveSnakeHead();

	EXPECT_EQ(snek.snakeBody[0].segmentXpos, -1);

	snek.snakeDirection = NORTH;
	snek.MoveSnakeHead();

	EXPECT_EQ(snek.snakeBody[0].segmentYpos, -1);
}

TEST(Snek, WillSnakeHeadWrapOnScreenBounds) {
	Snek snek;

	snek.snakeBody[0].segmentXpos = 10;

	snek.WrapSnakeOnScreenBounds();

	EXPECT_EQ(10, snek.snakeBody[0].segmentXpos);

	snek.snakeBody[0].segmentYpos = GRID_HOR_MAX + 1;

	snek.WrapSnakeOnScreenBounds();

	EXPECT_EQ(0, snek.snakeBody[0].segmentYpos);
}