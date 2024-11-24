//#include "Snek.h"
//
//Snek::Snek()
//{
//}
//
//Snek::~Snek()
//{
//};
//
//void Snek::MoveSnakeBody()
//{
//    for (int i = snakeLengthCurrent; i > 0; --i)
//    {
//        snakeBody[i].segmentXpos = snakeBody[i - 1].segmentXpos;
//        snakeBody[i].segmentYpos = snakeBody[i - 1].segmentYpos;
//    }
//}
//
//void Snek::MoveSnakeHead()
//{
//    switch (snakeDirection)
//    {
//    case SOUTH:
//        snakeBody[SNAKE_HEAD].segmentYpos += 1;
//        break;
//    case WEST:
//        snakeBody[SNAKE_HEAD].segmentXpos -= 1;
//        break;
//    case EAST:
//        snakeBody[SNAKE_HEAD].segmentXpos += 1;
//        break;
//    case NORTH:
//        snakeBody[SNAKE_HEAD].segmentYpos -= 1;
//        break;
//    default:
//        break;
//    }
//}
//
//Vec2Int Snek::HeadTouchFruit(Vec2Int t_pos, int t_randA, int t_randB)
//{
//    bool headTouchingFruitX = snakeBody[SNAKE_HEAD].segmentXpos == t_pos.x;
//    bool headTouchingFruitY = snakeBody[SNAKE_HEAD].segmentYpos == t_pos.y;
//
//    if (headTouchingFruitX && headTouchingFruitY)
//    {
//        snakeLengthCurrent++;
//        t_pos.x = t_randA % GRID_HOR_MAX;
//        t_pos.y = t_randB % GRID_VER_MAX;
//    }
//
//    Vec2Int output = { t_pos.x, t_pos.y };
//
//    return output;
//}
//
//void Snek::WrapSnakeOnScreenBounds()
//{
//    if (snakeBody[SNAKE_HEAD].segmentXpos > GRID_HOR_MAX)    snakeBody[SNAKE_HEAD].segmentXpos = 0;
//    if (snakeBody[SNAKE_HEAD].segmentXpos < 0)               snakeBody[SNAKE_HEAD].segmentXpos = GRID_HOR_MAX;
//    if (snakeBody[SNAKE_HEAD].segmentYpos > GRID_VER_MAX)    snakeBody[SNAKE_HEAD].segmentYpos = 0;
//    if (snakeBody[SNAKE_HEAD].segmentYpos < 0)               snakeBody[SNAKE_HEAD].segmentYpos = GRID_VER_MAX;
//}
//
//void Snek::CheckIfSnakeIntersects()
//{
//    for (int i = 1; i < snakeLengthCurrent; i++)
//    {
//        bool snakeHeadOverlapsBodySegmentX = snakeBody[SNAKE_HEAD].segmentXpos == snakeBody[i].segmentXpos;
//
//        bool snakeHeadOVerlapsBodySegmentY = snakeBody[SNAKE_HEAD].segmentYpos == snakeBody[i].segmentYpos;
//
//        if (snakeHeadOverlapsBodySegmentX && snakeHeadOVerlapsBodySegmentY)
//        {
//            snakeLengthCurrent = i;
//        }
//    }
//}