
#include "Config.h"
#include "World.h"
#include "Interface.h"

//Holds the current time
double timecount;

//Clock restarts counting from here after a pause
double countFrom = 0;

//The game timer
cPrecisionClock gameTimer;


/**
 * @brief States the game is  started and starts clock
 */
void startGameClock(){
    gameTimer.start();
    gameStarted = true;
}

/**
 * @brief Resumes the game timer
 */
void resumeGameClock(){
    gameTimer.reset(countFrom);
    gameTimer.start();
}

/**
 * @brief Pauses the game clock
 */
void pauseGameClock(){
    countFrom = gameTimer.stop();
    paused = true;
}

/**
 * @brief Updates the game clock whilst the game is running
 */
void updateClock(){
    if (gameFinished == false)
    {
        timecount = gameTimer.getCurrentTimeSeconds();
        string sTimecount = to_string(timecount);
        clockInfo->setText("Current Time: " + sTimecount );
        
    }
}

/**
 * @brief Used when the end of a level is reached
 */
void endClock(){
    timecount = gameTimer.stop();
}

