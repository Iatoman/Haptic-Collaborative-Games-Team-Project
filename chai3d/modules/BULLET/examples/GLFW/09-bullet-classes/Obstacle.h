#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "chai3d.h"
#include <GLFW/glfw3.h>
using namespace chai3d;
using namespace std;

#include "CBullet.h"

class Obstacle //: cBulletBox
{

public:
    Obstacle(   cBulletWorld* environment, cBulletBox* container, 
                double sizeX, double sizeY, double sizeZ, 
                double posX, double posY, double posZ); 



private:
    cBulletBox* obstacle;
    cMaterial mat;





};

#endif