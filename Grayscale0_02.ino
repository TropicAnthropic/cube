#define ABG_IMPLEMENTATION
#define ABG_SYNC_SLOW_DRIVE
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

void setup()
{
  a.begin();
  screenBuffer = a.getBuffer();
  a.startGray(); 
}

void loop()
{
  if(!a.nextFrame())
    return;
  render();
  movePlayer();
  fillBackground();
}

void render()
{

  Sprites::drawOverwrite(64, 32, box, frameNumber);
  if(++frameNumber==3) frameNumber=0;


// Draw Player  
  Sprites::drawOverwrite(playerX, playerY, box, frameNumber);
  if(++frameNumber==3) frameNumber=0;
//
}

void movePlayer()
{
  int r = rand() % 4;
  if (r == 0) {playerX++;}
  if (r == 1) {playerX--;}
  if ( r== 2) {playerY++;}
  if (r == 3) {playerY--;}  
}

void fillBackground()
{

}