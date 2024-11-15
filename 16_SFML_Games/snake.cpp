#include <SFML/Graphics.hpp>
#include <time.h>

#include "Snek.h"
#include "Fruit.h"

using namespace sf;

const int PIXELS_PER_SQUARE     = 16;
const int WINDOW_WIDTH          = PIXELS_PER_SQUARE * GRID_HOR_MAX;
const int WINDOW_HEIGHT         = PIXELS_PER_SQUARE * GRID_VER_MAX;

Snek m_snek;

Fruit m_fruit;

void InitialiseScreenAndPlayfield()
{
    Texture t1White, t2Red;
    t1White.loadFromFile("images/snake/white.png");
    t2Red.loadFromFile("images/snake/red.png");

    Sprite spriteBackground(t1White);
    Sprite spriteSnake(t2Red);
}

void Tick()
{
    m_snek.MoveSnakeBody();

    m_snek.MoveSnakeHead();

    Vec2Int fruitPosition = m_snek.HeadTouchFruit(m_fruit.m_fruitStruct.posX, m_fruit.m_fruitStruct.posY,rand(), rand());
    m_fruit.m_fruitStruct.posX = fruitPosition.x;
    m_fruit.m_fruitStruct.posY = fruitPosition.y;

    m_snek.WrapSnakeOnScreenBounds();

    m_snek.CheckIfSnakeIntersects();
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

    if (Keyboard::isKeyPressed(Keyboard::Left))     m_snek.snakeDirection = WEST;
    if (Keyboard::isKeyPressed(Keyboard::Right))    m_snek.snakeDirection = EAST;
    if (Keyboard::isKeyPressed(Keyboard::Up))       m_snek.snakeDirection = NORTH;
    if (Keyboard::isKeyPressed(Keyboard::Down))     m_snek.snakeDirection = SOUTH;
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

    for (int i = 0; i < m_snek.snakeLengthCurrent; i++)
    {
        int snakeSegmentScreenXPos = m_snek.snakeBody[i].segmentXpos * PIXELS_PER_SQUARE;
        int snakeSegmentScreenYPos = m_snek.snakeBody[i].segmentYpos * PIXELS_PER_SQUARE;
        t_spriteSnake.setPosition(snakeSegmentScreenXPos, snakeSegmentScreenYPos);
        t_window.draw(t_spriteSnake);
    }

    int fruitScreenXPos = m_fruit.m_fruitStruct.posX * PIXELS_PER_SQUARE;
    int fruitScreenYPos = m_fruit.m_fruitStruct.posY * PIXELS_PER_SQUARE;
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

    while (window.isOpen())
    {
        GetInput(window);
        HandleTickDelay(window, clock, tickTimer);
        DrawGame(window, spriteBackground, spriteSnake);
    }
return 0;
}