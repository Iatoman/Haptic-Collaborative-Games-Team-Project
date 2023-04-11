#include "World.h"
#include "Game.h"
#include "Map.h"
#include "Board.h"
#include "Ball.h"
#include "Haptic.h"
#include "Interface.h"
#include "Config.h"
#include "Mouse.h"

void startGame()
{
    createStartscreen();
    createPausescreen();
    clockInterface();

    runMainGraphicsLoop();
}

/**
 * @brief check whether the ball reaches the goal position
 * 
 */
void doWinCheck()
{
    if (gameFinished <1)
    {
        double desX = -1.1;         // x-coordinate of destination point
        double desY = -1.0;          // y-coordinate of destination point

        double dx = fabs(ball->getGlobalPos().x() - desX);
        double dy = fabs(ball->getGlobalPos().y() - desY);

        double range = 0.2;         // detection range

        if (dx < range && dy < range)
        {
            endClock();
            createCompletedScreen((int) timecount, 1);
            gameFinished ++;
            cout << gameFinished<<endl;
            // completedMessage->setText("");
        }
    }
}

/**
 * @brief check whether the ball falls out of the board
 * 
 * @return whether the ball is fallen
 */
bool isBallFallen()
{
    return (ball->getLocalPos().z() < -1.0);
}

/**
 * @brief reset the ball position and the mouse potential field position
 * 
 */
void resetBall()
{
    cVector3d initialPos(1.0, -1.0, 1);
    ball->setLocalPos(initialPos);
    selectedPoint = initialPos;
}
