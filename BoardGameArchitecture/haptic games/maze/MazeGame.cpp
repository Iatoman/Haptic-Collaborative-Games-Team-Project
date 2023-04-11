#include "World.h"
#include "Mouse.h"
#include "Game.h"
#include "Map.h"
#include "Ball.h"
#include "Haptic.h"
#include "Interface.h"
#include "Board.h"

int main()
{
    initWorld();
    initHapticDevice(world);

    cBulletBox *board = createBoard(world);

    ball = createBall(world, 0.05);
    setBallSpawnPoint(ball, 1.0, -1.0, 1);
    
    addObstacleBox(world, 0.8, 0.4, 0.3, 0.5, -0.8, 0.1);
    addObstacleBox(world, 0.6, 0.4, 0.2, -0.2, -0.1, 0.1);
    addObstacleBox(world, 0.6, 0.4, 0.2, 0.6, 0.3, 0.1);
    addObstacleBox(world, 0.8, 0.3, 0.2, -0.2, 0.7, 0.1);
    addObstacleBox(world, 0.2, 0.2, 0.2, -0.8, 1.0, 0.1);
    addObstacleBox(world, 0.05, 1.2, 0.1, -0.8, -0.6, 0.1);

    createGoal(world, cVector3d(-1.1, -1.0, 0.0), 0.1, 0.11);
    
    addBoundaries(world, true, true, true, false);
    resetBall();
    
    startGame();
    
    return 0;
}
