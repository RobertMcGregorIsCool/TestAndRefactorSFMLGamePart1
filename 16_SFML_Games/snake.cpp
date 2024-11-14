#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int GRID_HOR=30,GRID_VER=20;
int pixelsPerSquare=16;
int windowWidth = pixelsPerSquare*GRID_HOR;
int windowHeight = pixelsPerSquare*GRID_VER;

int direction;

int snakeLength =4;

struct Snake 
{ int segmentXpos,segmentYpos;}  snakeBody[100];

struct Fruit
{ int x,y;} fruit;

void Tick()
 {
    for (int i = snakeLength; i > 0; --i)
    {  
        snakeBody[i].segmentXpos = snakeBody[i-1].segmentXpos; 
        snakeBody[i].segmentYpos = snakeBody[i-1].segmentYpos;
    }

    if (direction==0) snakeBody[0].segmentYpos+=1;      
    if (direction==1) snakeBody[0].segmentXpos-=1;        
    if (direction==2) snakeBody[0].segmentXpos+=1;         
    if (direction==3) snakeBody[0].segmentYpos-=1;   

    if ((snakeBody[0].segmentXpos==fruit.x) && (snakeBody[0].segmentYpos==fruit.y)) 
     {
        snakeLength++; 
        fruit.x=rand()%GRID_HOR; 
        fruit.y=rand()%GRID_VER;
    }

    if (snakeBody[0].segmentXpos>GRID_HOR)  snakeBody[0].segmentXpos=0;  
    if (snakeBody[0].segmentXpos<0)         snakeBody[0].segmentXpos=GRID_HOR;
    if (snakeBody[0].segmentYpos>GRID_VER)  snakeBody[0].segmentYpos=0;  
    if (snakeBody[0].segmentYpos<0)         snakeBody[0].segmentYpos=GRID_VER;
 
    for (int i = 1; i < snakeLength; i++)
    {
        if (snakeBody[0].segmentXpos == snakeBody[i].segmentXpos && 
            snakeBody[0].segmentYpos == snakeBody[i].segmentYpos)  
        {
            snakeLength = i;
        }
    }
 }

int snake()
{  
    srand(time(0));

    RenderWindow window(VideoMode(windowWidth, windowHeight), "Snake Game!");

    Texture t1White,t2Red;
    t1White.loadFromFile("images/snake/white.png");
    t2Red.loadFromFile("images/snake/red.png");

    Sprite spriteBackground(t1White);
    Sprite spriteSnake(t2Red);

    Clock clock;
    float tickTimer=0, tickDelay=0.1;

    fruit.x=10;
    fruit.y=10; 
    
    while (window.isOpen())
    {
        float elapsedTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        tickTimer += elapsedTime; 

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)      
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) direction=1;   
        if (Keyboard::isKeyPressed(Keyboard::Right)) direction=2;    
        if (Keyboard::isKeyPressed(Keyboard::Up)) direction=3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) direction=0;

        if (tickTimer>tickDelay) 
        {
            tickTimer=0; 
            Tick();
        }

   ////// draw  ///////
    window.clear();

    for (int i=0; i<GRID_HOR; i++) 
      for (int j=0; j<GRID_VER; j++) 
        { 
          spriteBackground.setPosition(i * pixelsPerSquare, j * pixelsPerSquare);  
          window.draw(spriteBackground); 
        }

    for (int i=0;i<snakeLength;i++)
        { 
        spriteSnake.setPosition(snakeBody[i].segmentXpos * pixelsPerSquare, snakeBody[i].segmentYpos * pixelsPerSquare);
        window.draw(spriteSnake); 
        }
   
    spriteSnake.setPosition(fruit.x * pixelsPerSquare, fruit.y * pixelsPerSquare);  
    window.draw(spriteSnake);    

    window.display();
    }

    return 0;
}
