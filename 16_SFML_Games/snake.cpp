#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int GRID_HOR_MAX = 30,GRID_VER_MAX= 20;
const int PIXELS_PER_SQUARE     = 16;
const int WINDOW_WIDTH          = PIXELS_PER_SQUARE * GRID_HOR_MAX;
const int WINDOW_HEIGHT         = PIXELS_PER_SQUARE * GRID_VER_MAX;

int direction   = 0;
const int SOUTH = 0;
const int WEST  = 1;
const int EAST  = 2;
const int NORTH = 3;

int snakeHead   = 0;
int snakeLengthCurrent = 4;
const int SNAKE_LENGTH_MAX = 100;

int fruitStartingPos = 10;

struct Snake
{
    int segmentXpos = 0;
    int segmentYpos = 0;
}   snakeBody[SNAKE_LENGTH_MAX];

struct Fruit
{
    int posX = 0;
    int posY = 0;
} fruit;

void MoveSnakeBody()
{
    for (int i = snakeLengthCurrent; i > 0; --i)
    {
        snakeBody[i].segmentXpos = snakeBody[i - 1].segmentXpos;
        snakeBody[i].segmentYpos = snakeBody[i - 1].segmentYpos;
    }
}

void MoveSnakeHead()
{
    if (direction == SOUTH) snakeBody[snakeHead].segmentYpos += 1;
    if (direction == WEST)  snakeBody[snakeHead].segmentXpos -= 1;
    if (direction == EAST)  snakeBody[snakeHead].segmentXpos += 1;
    if (direction == NORTH) snakeBody[snakeHead].segmentYpos -= 1;
}

void HeadTouchFruit()
{
    bool headTouchingFruitX = snakeBody[snakeHead].segmentXpos == fruit.posX;
    bool headTouchingFruitY = snakeBody[snakeHead].segmentYpos == fruit.posY;

    if (headTouchingFruitX && headTouchingFruitY)
    {
        snakeLengthCurrent++;
        fruit.posX = rand() % GRID_HOR_MAX;
        fruit.posY = rand() % GRID_VER_MAX;
    }
}

void WrapSnakeOnScreenBounds()
{
    if (snakeBody[snakeHead].segmentXpos > GRID_HOR_MAX)    snakeBody[snakeHead].segmentXpos = 0;
    if (snakeBody[snakeHead].segmentXpos < 0)               snakeBody[snakeHead].segmentXpos = GRID_HOR_MAX;
    if (snakeBody[snakeHead].segmentYpos > GRID_VER_MAX)    snakeBody[snakeHead].segmentYpos = 0;
    if (snakeBody[snakeHead].segmentYpos < 0)               snakeBody[snakeHead].segmentYpos = GRID_VER_MAX;
}

void CheckIfSnakeIntersects()
{
    for (int i = 1; i < snakeLengthCurrent; i++)
    {
        bool snakeHeadOverlapsBodySegmentX = snakeBody[snakeHead].segmentXpos == snakeBody[i].segmentXpos;

        bool snakeHeadOVerlapsBodySegmentY = snakeBody[snakeHead].segmentYpos == snakeBody[i].segmentYpos;

        if (snakeHeadOverlapsBodySegmentX && snakeHeadOVerlapsBodySegmentY)
        {
            snakeLengthCurrent = i;
        }
    }
}

void InitialiseScreenAndPlayfield()
{
    Texture t1White, t2Red;
    t1White.loadFromFile("images/snake/white.png");
    t2Red.loadFromFile("images/snake/red.png");

    Sprite spriteBackground(t1White);
    Sprite spriteSnake(t2Red);

    fruit.posX = fruitStartingPos;
    fruit.posY = fruitStartingPos;
}

void Tick()
{
    MoveSnakeBody();

    MoveSnakeHead();

    HeadTouchFruit();

    WrapSnakeOnScreenBounds();

    CheckIfSnakeIntersects();
}

void HandleTickDelay(RenderWindow & t_window, Clock & t_clock, float & t_tickTimer)
{
    float tickDelay = 0.1f;

    float elapsedTime = t_clock.getElapsedTime().asSeconds();
    t_clock.restart();
    t_tickTimer += elapsedTime;

    if (t_tickTimer > tickDelay)
    {
        t_tickTimer = 0;
        Tick();
    }
}

void GetInput(RenderWindow & t_window)
{
    Event eventCurrent;
    while (t_window.pollEvent(eventCurrent))
    {
        if (eventCurrent.type == Event::Closed) t_window.close();
    }

    if (Keyboard::isKeyPressed(Keyboard::Left))     direction = WEST;
    if (Keyboard::isKeyPressed(Keyboard::Right))    direction = EAST;
    if (Keyboard::isKeyPressed(Keyboard::Up))       direction = NORTH;
    if (Keyboard::isKeyPressed(Keyboard::Down))     direction = SOUTH;
}

void DrawGame(RenderWindow& t_window, Sprite& t_spriteBg, Sprite& t_spriteSnake)
{
    t_window.clear();

    for (int iX = 0; iX < GRID_HOR_MAX; iX++)
        for (int iY = 0; iY < GRID_VER_MAX; iY++)
        {
            t_spriteBg.setPosition(iX * PIXELS_PER_SQUARE, iY * PIXELS_PER_SQUARE);
            t_window.draw(t_spriteBg);
        }

    for (int i = 0; i < snakeLengthCurrent; i++)
    {
        int snakeSegmentScreenXPos = snakeBody[i].segmentXpos * PIXELS_PER_SQUARE;
        int snakeSegmentScreenYPos = snakeBody[i].segmentYpos * PIXELS_PER_SQUARE;
        t_spriteSnake.setPosition(snakeSegmentScreenXPos, snakeSegmentScreenYPos);
        t_window.draw(t_spriteSnake);
    }

    int fruitScreenXPos = fruit.posX * PIXELS_PER_SQUARE;
    int fruitScreenYPos = fruit.posY * PIXELS_PER_SQUARE;
    t_spriteSnake.setPosition(fruitScreenXPos, fruitScreenYPos);
    t_window.draw(t_spriteSnake);

    t_window.display();
}

int snake()
{  
    srand(time(0));

    Clock clock;
    float tickTimer = 0;

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game!");

    Texture t1White, t2Red;
    t1White.loadFromFile("images/snake/white.png");
    t2Red.loadFromFile("images/snake/red.png");

    Sprite spriteBackground(t1White);
    Sprite spriteSnake(t2Red);

    fruit.posX = fruitStartingPos;
    fruit.posY = fruitStartingPos;

    while (window.isOpen())
    {
        GetInput(window);
        HandleTickDelay(window, clock, tickTimer);
        DrawGame(window, spriteBackground, spriteSnake);
    }
return 0;
}