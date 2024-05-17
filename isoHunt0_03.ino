#define ABG_IMPLEMENTATION
#define ABG_SYNC_SLOW_DRIVE
//#define ABG_L4_Triplane
#define ABG_TIMER4
#include "ArduboyG.h"
ArduboyG_Config<ABG_Mode::L4_Triplane> a;

#include <Arduboy2.h>
#include "gfx.h"
Arduboy2 arduboy;

unsigned char * screenBuffer;
int frameNumber = 0;

// Global Variables
int direction = 1;
int playerX = 60; // 120
int playerY = 60; // 120
int pX; // player screen cords
int pY;

uint8_t screen[76];

void setup()
{
  a.begin();
  screenBuffer = a.getBuffer();
  a.startGray(); 
  newGame();
}

void loop()
{
  if(!a.nextFrame())
    return;

  movePlayer();
  calcPlayer();
  render();
}

void render()
{

  Sprites::drawExternalMask(24, -1, backgnd1, backgnd1Mask, frameNumber, 0);

  //fillFloor();

  //Sprites::drawExternalMask(64, 0, boxHole1, boxMask, frameNumber, 0);
  
  //fillBackground();

  Sprites::drawExternalMask(pX, pY, player1, player1Mask, frameNumber, 0);

  if(++frameNumber==3) frameNumber=0;
}

void calcPlayer()
{
  pX = playerX/3;
  pY = playerY/3;

  

  pX = pX + 36;
  pY = pY + 18;
}

void movePlayer()
{
  if (direction == 1)
  {
    playerX++;
  }

  if (direction == 2)
  {
    playerX--;
  }

  if (playerX > 120)
  {
    direction = 2;
  }

  if (playerX < 0)
  {
    direction = 1;
  }
}

void newGame()
{
  for (int i = 0; 75 > i; i ++) // populate level array
  {
    int r = rand() % 5;
    if (r == 1)
    {
      screen[i] = 1;
    }
  }
}

void fillFloor()
{
  int xOffset = 54;
  int yOffset = 20;
  for (int x = 0; 5 > x; x ++)
  {
    for (int y = 0; 5 > y; y ++)
    {
        int xDraw = x * 16;
        int yDraw = y * 4;
        Sprites::drawExternalMask(xDraw + xOffset, yDraw + yOffset, floor1, floorMask, frameNumber, 0);

      xOffset = xOffset - 8;
    }
    xOffset = xOffset + 32;
    yOffset = yOffset + 4;
  }
}

void fillBackground()
{
  int i = 0;
  int xOffset = 56;
  int yOffset = 16;
  for (int x = 0; 5 > x; x ++)
  {
    for (int y = 0; 5 > y; y ++)
    {
      //if (screen[i] == 1)
      //{
        int xDraw = x * 16;
        int yDraw = y * 4;

        Sprites::drawExternalMask(xDraw + xOffset, yDraw + yOffset, boxHole1, boxMask, frameNumber, 0);
      //}
      i++;
      xOffset = xOffset - 8;
    }
    xOffset = xOffset + 32;
    yOffset = yOffset + 4;
  }
}