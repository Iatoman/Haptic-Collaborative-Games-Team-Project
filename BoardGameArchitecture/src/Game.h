#ifndef GAME_H
#define GAME_H

#include "chai3d.h"
#include <GLFW/glfw3.h>
using namespace chai3d;
using namespace std;

#include "CBullet.h"

void startGame();

// check whether the ball reaches the goal position
void doWinCheck();

// check whether the ball falls out of the board
bool isBallFallen();

// reset the ball position and the mouse potential field position
void resetBall();


#endif // GAME_H