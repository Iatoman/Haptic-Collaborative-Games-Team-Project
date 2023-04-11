#ifndef BALL_H_
#define BALL_H_

#include "chai3d.h"
#include <GLFW/glfw3.h>

using namespace chai3d;
using namespace std;

#include "CBullet.h"

// A function to create a ball
cBulletSphere* createBall(cBulletWorld* world, double radius);
// A function to set material of the ball
void setBallMaterial(cBulletSphere* ball);
// A function to set collision of the ball
void setBallCollision(cBulletSphere* ball, double toolRadius);
// A function to set location of the ball
void setBallSpawnPoint(cBulletSphere* ball, double x, double y, double z);
// A function to set mass of the ball
void setBallMass(cBulletSphere* ball, double mass);
// A function to change color of the ball
void changeBallColor(cBulletSphere* ball, cMaterial mat); 

#endif
