/**
 * This file contains all the code to create and manipulate
 * a board object.
 */

#include "Board.h"

tuple<double, double, double> initalPos; // a tuple for getting the board dimensions
bool posFlag = false; //a Flag to help with storing the initial board position

//Variables to store initial board positions
double initialX; double initialY; double initialZ;
double posX; double posY; double posZ;

// Pointers to the board boundaries
cBulletBox* rightWall;
cBulletBox* leftWall;
cBulletBox* frontWall;
cBulletBox* backWall;

/**
 * @brief Retrieve a standard material to apply to an object
 *
 * @return cMaterial a standard red cMaterial with some physical properties
 */
cMaterial getStandardMaterial()
{
    cMaterial mat;
    mat.setRedFireBrick();
    mat.setStiffness(0.3 /* * maxStiffness*/); //GO DEFINE MAX STIFFNESS
    mat.setDynamicFriction(0.9);
    mat.setStaticFriction(0.9);

    return mat;
}

/**
 * @brief Creates a board with set dimensions (2.5, 2.5, 0.05) at (0,0,0)
 *
 * @param container a cBulletWorld that the board is to be created in
 * 
 * @return cBulletBox* a pointer to a board object
 */
cBulletBox* createBoard(cBulletWorld* container)
{
    return createBoard(container, 2.5, 2.5, 0.05);
}

/**
 * @brief Creates a board with a set thickness (0.05) at (0,0,0)
 *
 * @param container a cBulletWorld that the board is to be created in
 * @param length the length used to create the board
 * @param width the width used to create the board
 * 
 * @return cBulletBox* a pointer to a board object
 */
cBulletBox* createBoard(cBulletWorld* container, 
                        double length, double width)
{
    return createBoard(container, length, width, 0.05);
}

/**
 * @brief Creates a board at global position (0,0,0) in a world    
 *
 * @param container a cBulletWorld that the board is to be created in
 * @param length the length used to create the board
 * @param width the width used to create the board
 * @param depth the depth (thickness) used to create the board
 * 
 * @return cBulletBox* a pointer to a board object
 */
cBulletBox* createBoard(cBulletWorld* container, 
                        double length, double width, double depth)
{
    cBulletBox* board;
    board = new cBulletBox(container, length, width, depth);
    container->addChild(board);

    cMaterial mat = getStandardMaterial();
    board->setMaterial(mat);
    board->buildDynamicModel();
    board->createAABBCollisionDetector(0.06); //hardcoding toolRadius at 0.06
    setBoardPosition(board, 0, 0, 0);

    return board;
}

/**
 * @brief Get the position of the centre of a board in the world. 
 *
 * @param board a board to get the position of
 * 
 * @return cVector3d the position vector of the centre of the given board
 */
cVector3d getBoardPosition(cBulletBox* board)
{
    return board->getLocalPos();
}

/**
 * @brief Get dimensions of a board.
 *
 * @param board a board to get the position of
 * 
 * @return a 3-tuple of the X,Y,Z dimensions of the given board
 */
tuple<double, double, double> getBoardDimensions(cBulletBox* board)
{
    return make_tuple(board->getSizeX(), board->getSizeY(), board->getSizeZ());
}

/**
 * @brief Set the position of the centre of the board in a world
 *
 * @param board a board to set the position of
 * @param posX the X coordinate to set the board to
 * @param posY the Y coordinate to set the board to
 * @param posZ the Z coordinate to set the board to
 * 
 * 
 */
void setBoardPosition(cBulletBox* board, 
                      double posX, double posY, double posZ)
{
    if (!posFlag)
    {
        initialX = posX;
        initialY = posY;
        initialZ = posZ;
        //initialPos = make_tuple(posX, posY, posZ); //identifier undefined
    }
    posFlag = true;

    board->setLocalPos(cVector3d(posX, posY, posZ));
}

/**
 * @brief Set the position of the centre of the board in a world
 *
 * @param board a board to set the position of
 * @param posVector a cVector3d object containing the new board position
 * 
 * 
 */
void setBoardPosition(cBulletBox* board, cVector3d posVector)
{
    if (!posFlag)
    {
        initialX = posVector.x();
        initialY = posVector.y();
        initialZ = posVector.z();
        //initialPos = make_tuple(posX, posY, posZ); //identifier undefined
    }
    posFlag = true;

    board->setLocalPos(posVector);
}

/**
 * @brief Set the position of the X coordinate of the board in a world
 *
 * @param board a board to set the position of
 * @param pos a double containing the new board X position
 * 
 */
void setBoardPositionX(cBulletBox* board, double pos)
{
    posY = board->getLocalPos().y();
    posZ = board->getLocalPos().z();
    board->setLocalPos(cVector3d(pos, posY, posZ));
}

/**
 * @brief Set the position of the Y coordinate of the board in a world
 *
 * @param board a board to set the position of
 * @param pos a double containing the new board Y position
 * 
 */
void setBoardPositionY(cBulletBox* board, double pos)
{
    posX = board->getLocalPos().x();
    posZ = board->getLocalPos().z();
    board->setLocalPos(cVector3d(posX, pos, posZ));
}

/**
 * @brief Set the position of the Z coordinate of the board in a world
 *
 * @param board a board to set the position of
 * @param pos a double containing the new board Z position
 * 
 */
void setBoardPositionZ(cBulletBox* board, double pos)
{
    posX = board->getLocalPos().x();
    posY = board->getLocalPos().y();
    board->setLocalPos(cVector3d(posX, posY, pos));
}

/**
 * @brief Changes the dimensions of the board
 *
 * @param container a cBulletWorld object on which to operate in
 * @param board a cBulletbox object to change the size of 
 * @param length the new length of the board
 * @param width the new width of the board
 * @param depth the new depth of the board

 * @warning WILL NOT CHANGE DIMENSIONS OF ANY OBSTACLES
 */
void setBoardDimensions(cBulletWorld* container, cBulletBox* board, double length, double width, double depth)
{
    cVector3d pos = getBoardPosition(board);
    delete board;
    cBulletBox* board_new = createBoard(container, length, width, depth);
    setBoardPosition(board_new, pos);
}

/**
 * @brief Reset board back to initial position that it was when it was created
 *
 * @param board a board object to reset the position of
 *
 */
void resetBoardPosition(cBulletBox* board)
{
    board->setLocalPos(initialX, initialY, initialZ);
}

/**
 * @brief Add a cBulletBox into the world to act as an obstacle
 *
 * @param container a cBulletWorld object on which to operate in
 * @param sizeX size X of the new obstacle
 * @param sizeY size Y of the new obstacle
 * @param sizeZ size Z of the new obstacle
 * @param X an X position in the world to create the new obstacle at 
 * @param Y an Y position in the world to create the new obstacle at 
 * @param Z an Z position in the world to create the new obstacle at 
 * 
 * @return a pointer to the new obstacle
 */
cBulletBox* addObstacleBox(cBulletWorld* container, double sizeX, double sizeY, double sizeZ,
                    double X, double Y, double Z)
{
    cBulletBox* newObstacle = new cBulletBox(container, sizeX, sizeY, sizeZ);
    container->addChild(newObstacle);
    cMaterial mat = getStandardMaterial();
    mat.setBlueCornflower();
    newObstacle->setMaterial(mat);
    newObstacle->buildDynamicModel();
    newObstacle->createAABBCollisionDetector(0.06); //TOOLRADIUS
    newObstacle->setLocalPos(X,Y,Z);

    return newObstacle;
}

/**
 * @brief Add a cBulletCylinder into the world to act as an obstacle
 *
 * @param container a cBulletWorld object on which to operate in
 * @param height height of the new obstacle
 * @param radius radius of the new obstacle
 * @param X an X position in the world to create the new obstacle at 
 * @param Y an Y position in the world to create the new obstacle at 
 * @param Z an Z position in the world to create the new obstacle at 
 * 
 * @return a pointer to the new obstacle
 */
cBulletCylinder* addObstacleCylinder(cBulletWorld* container, double height, double radius,
                    double X, double Y, double Z)
{
    cBulletCylinder* newObstacle = new cBulletCylinder(container, height, radius);
    container->addChild(newObstacle);
    cMaterial mat = getStandardMaterial();
    mat.setBlueCornflower();
    newObstacle->setMaterial(mat);
    newObstacle->buildDynamicModel();
    newObstacle->createAABBCollisionDetector(0.06); //TOOLRADIUS
    newObstacle->setLocalPos(X,Y,Z);

    return newObstacle;
}

/**
 * @brief Creates a goal in a world that the ball has to move to to win the game
 *
 * @param container a cBulletWorld object on which to operate in
 * @param position a cVector3d of the position in the world to set the goal to
 * @param height the height of the goal
 * @param radius radius of the goal
 * 
 */
void createGoal(cBulletWorld* container, cVector3d position, double height, double radius)
{
    cBulletCylinder* goal = new cBulletCylinder(container, height, radius);
    container->addChild(goal);
    cMaterial goalMat = getStandardMaterial();
    goalMat.setGreenLawn();
    goal->setMaterial(goalMat);
    goal->setLocalPos(position);
}

/**
 * @brief Add bounding walls to prevent the ball from falling off the board
 *
 * @param container     a cBulletWorld object on which to operate in
 * @param leftWall      whether to create left wall
 * @param rightWall     whether to create right wall
 * @param frontWall     whether to create front wall
 * @param backWall      whether to create back wall
 * 
 */
void addBoundaries(cBulletWorld* container, bool leftWall, bool rightWall, bool frontWall, bool backWall)
{
    
    cMaterial mat = getStandardMaterial();
    mat.setBlueCornflower();

    if (leftWall)
    {   
        cBulletBox* leftWall;
        leftWall = new cBulletBox(container, 2.6, 0.1,0.2);
        container->addChild(leftWall);
        leftWall->setMaterial(mat);
        leftWall->buildDynamicModel();
        leftWall->createAABBCollisionDetector(0.06); //TOOLRADIUS
        leftWall->setLocalPos(0.0, -1.25, 0.1);
    }
 
    if (rightWall)
    {
        cBulletBox* rightWall;
        rightWall = new cBulletBox(container, 2.6, 0.1,0.2);
        container->addChild(rightWall);
        rightWall->setMaterial(mat);
        rightWall->buildDynamicModel();
        rightWall->createAABBCollisionDetector(0.06); //TOOLRADIUS
        rightWall->setLocalPos(0.0, 1.25, 0.1);
        
    }

    if (frontWall)
    {
        cBulletBox* frontWall;
        frontWall = new cBulletBox(container, 0.1, 2.6,0.2);
        container->addChild(frontWall);
        frontWall->setMaterial(mat);
        frontWall->buildDynamicModel();
        frontWall->createAABBCollisionDetector(0.06); //TOOLRADIUS
        frontWall->setLocalPos(1.25, 0, 0.1);
    }
 
    if (backWall)
    {
        cBulletBox* backWall;
        backWall = new cBulletBox(container, 0.1, 2.6,0.2);
        container->addChild(backWall);
        backWall->setMaterial(mat);
        backWall->buildDynamicModel();
        backWall->createAABBCollisionDetector(0.06); //TOOLRADIUS
        backWall->setLocalPos(-1.25, 0, 0.1);
    }
}
