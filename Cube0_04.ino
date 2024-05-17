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
int playerX = 64;
int playerY = 32;
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
  render();
  movePlayer();
}

void render()
{
  fillFloor();

  //Sprites::drawExternalMask(20, 20, bigFloor, bigFloorMask, frameNumber, 0);
  
  fillBackground();

  Sprites::drawExternalMask(playerX, playerY, box, boxMask, frameNumber, 0);

  if(++frameNumber==3) frameNumber=0;
}

void movePlayer()
{
  int r = rand() % 4;
  if (r == 0&&playerX<112) {playerX++;}
  if (r == 1&&playerX>0) {playerX--;}
  if ( r== 2&&playerY<48) {playerY++;}
  if (r == 3&&playerY>0) {playerY--;}  
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
  int xOffset = 54;
  int yOffset = 12;
  for (int x = 0; 5 > x; x ++)
  {
    for (int y = 0; 5 > y; y ++)
    {
      if (screen[i] == 1)
      {
        int xDraw = x * 16;
        int yDraw = y * 4;

        Sprites::drawExternalMask(xDraw + xOffset, yDraw + yOffset, box, boxMask, frameNumber, 0);
      }
      i++;
      xOffset = xOffset - 8;
    }
    xOffset = xOffset + 32;
    yOffset = yOffset + 4;
  }
}