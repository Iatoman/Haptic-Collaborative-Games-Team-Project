#ifndef BOARD_H
#define BOARD_H

#include "chai3d.h"
#include <GLFW/glfw3.h>
using namespace chai3d;
using namespace std;

#include "CBullet.h"

#include <tuple>

//Retrieve a standard material to apply to an object
cMaterial getStandardMaterial();

//Creates a board with set dimensions (2.5, 2.5, 0.05) at (0,0,0)
cBulletBox* createBoard(cBulletWorld* container);

//Creates a board with a set thickness (0.05) at (0,0,0)
cBulletBox* createBoard(cBulletWorld* container, double length, double width);

//Creates a board at global position (0,0,0) in a world    
cBulletBox* createBoard(cBulletWorld* container, double length, double width, double depth);

//Get the position of the centre of a board in the world. 
cVector3d getBoardPosition(cBulletBox* board);

//Get dimensions of a board. Returns a 3-tuple <x,y,z>
std::tuple<double, double, double> getBoardDimensions(cBulletBox* board);

//Set the position of the centre of the board in a world, arguments separate
void setBoardPosition(cBulletBox* board, double posX, double posY, double posZ);

//Set the position of the centre of the board in a world, given a pos vector
void setBoardPosition(cBulletBox* board, cVector3d posVector);

//Set the position of the X coordinate of the board in a world
void setBoardPositionX(cBulletBox* board, double pos);

//Set the position of the Y coordinate of the board in a world
void setBoardPositionY(cBulletBox* board, double pos);

//Set the position of the Z coordinate of the board in a world
void setBoardPositionZ(cBulletBox* board, double pos);

//Changes the dimensions of the board
void setBoardDimensions(cBulletBox* board, double length, double width, double depth);

//Reset board back to initial position that it was when it was created
void resetBoardPosition();

//Add a cBulletBox into the world to act as an obstacle
cBulletBox* addObstacleBox(cBulletWorld* container, double sizeX, double sizeY, double sizeZ, double X, double Y, double Z);

//Add a cBulletCylinder into the world to act as an obstacle
cBulletCylinder* addObstacleCylinder(cBulletWorld* container, double height, double radius,
                    double X, double Y, double Z);

//Creates a goal in a world that the ball has to move to to win the game
void createGoal(cBulletWorld* container, cVector3d position, double height, double radius);

void addBoundaries(cBulletWorld* container, bool leftWall, bool rightWall, bool frontWall, bool backWall);






#endif
