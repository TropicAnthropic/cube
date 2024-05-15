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
  fillBackground();

  Sprites::drawOverwrite(64, 32, floor1, frameNumber);

  Sprites::drawOverwrite(playerX, playerY, box, frameNumber);

  if(++frameNumber==3) frameNumber=0;
}

void movePlayer()
{
  int r = rand() % 4;
  if (r == 0&&playerX<128) {playerX++;}
  if (r == 1&&playerX>0) {playerX--;}
  if ( r== 2&&playerY<64) {playerY++;}
  if (r == 3&&playerY>0) {playerY--;}  
}

void newGame()
{
  for (int i = 0; 75 > i; i ++) // populate level array
  {
    int r = rand() % 2;
    if (r == 1)
    {
      screen[i] = 1;
    }
  }
}

void fillBackground()
{
  int i = 0;
  for (int x = 0; 8 > x; x ++)
  {
    for (int y = 0; 4 > y; y++)
    {
      if (screen[i] == 1)
      {
        int xDraw = x * 16;
        int yDraw = y * 16;
        Sprites::drawOverwrite(xDraw, yDraw, floor1, frameNumber);
      }
      i++;
    }
  }
}