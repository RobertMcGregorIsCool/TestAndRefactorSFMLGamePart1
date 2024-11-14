#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int GRID_HOR = 30,GRID_VER= 20;
const int PIXELS_PER_SQUARE     = 16;
const int WINDOW_WIDTH          = PIXELS_PER_SQUARE * GRID_HOR;
const int WINDOW_HEIGHT         = PIXELS_PER_SQUARE * GRID_VER;

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

void Tick()
 {
    for (int i = snakeLengthCurrent; i > 0; --i)
    {  
        snakeBody[i].segmentXpos = snakeBody[i-1].segmentXpos;
        snakeBody[i].segmentYpos = snakeBody[i-1].segmentYpos;
    }

    if (direction == SOUTH) snakeBody[snakeHead].segmentYpos += 1;
    if (direction == WEST)  snakeBody[snakeHead].segmentXpos -= 1;
    if (direction == EAST)  snakeBody[snakeHead].segmentXpos += 1;
    if (direction == NORTH) snakeBody[snakeHead].segmentYpos -= 1;

    if ((snakeBody[0].segmentXpos == fruit.posX) && 
        (snakeBody[0].segmentYpos == fruit.posY)) 
     {
        snakeLengthCurrent++; 
        fruit.posX = rand()%GRID_HOR; 
        fruit.posY = rand()%GRID_VER;
    }

    if (snakeBody[snakeHead].segmentXpos>GRID_HOR)  snakeBody[snakeHead].segmentXpos = 0;
    if (snakeBody[snakeHead].segmentXpos<0)         snakeBody[snakeHead].segmentXpos = GRID_HOR;
    if (snakeBody[snakeHead].segmentYpos>GRID_VER)  snakeBody[snakeHead].segmentYpos = 0;
    if (snakeBody[snakeHead].segmentYpos<0)         snakeBody[snakeHead].segmentYpos = GRID_VER;
 
    for (int i = 1; i < snakeLengthCurrent; i++)
    {
        if (snakeBody[snakeHead].segmentXpos == snakeBody[i].segmentXpos &&
            snakeBody[snakeHead].segmentYpos == snakeBody[i].segmentYpos)
        {
            snakeLengthCurrent = i;
        }
    }
 }

int snake()
{  
    srand(time(0));

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game!");

    Texture t1White,t2Red;
    t1White.loadFromFile("images/snake/white.png");
    t2Red.loadFromFile("images/snake/red.png");

    Sprite spriteBackground(t1White);
    Sprite spriteSnake(t2Red);

    Clock clock;
    float tickTimer = 0;
    float tickDelay = 0.1f;

    fruit.posX = fruitStartingPos;
    fruit.posY = fruitStartingPos; 
    
    while (window.isOpen())
    {
        float elapsedTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        tickTimer += elapsedTime; 

        Event eventCurrent;
        while (window.pollEvent(eventCurrent))
        {
            if (eventCurrent.type == Event::Closed)      
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))     direction = WEST;   
        if (Keyboard::isKeyPressed(Keyboard::Right))    direction = EAST;    
        if (Keyboard::isKeyPressed(Keyboard::Up))       direction = NORTH;
        if (Keyboard::isKeyPressed(Keyboard::Down))     direction = SOUTH;

        if (tickTimer > tickDelay) 
        {
            tickTimer = 0; 
            Tick();
        }

   ////// draw  ///////
    window.clear();

    for (int iX = 0; iX < GRID_HOR; iX++) 
      for (int iY = 0; iY < GRID_VER; iY++) 
        { 
          spriteBackground.setPosition(iX * PIXELS_PER_SQUARE, iY * PIXELS_PER_SQUARE);
          window.draw(spriteBackground);
        }

    for (int i=0;i<snakeLengthCurrent;i++)
        { 
        spriteSnake.setPosition(snakeBody[i].segmentXpos * PIXELS_PER_SQUARE, snakeBody[i].segmentYpos * PIXELS_PER_SQUARE);
        window.draw(spriteSnake); 
        }
   
    spriteSnake.setPosition(fruit.posX * PIXELS_PER_SQUARE, fruit.posY * PIXELS_PER_SQUARE);  
    window.draw(spriteSnake);    

    window.display();
    }
    return 0;
}
