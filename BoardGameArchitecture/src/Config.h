#include "../../chai3d-3.2.0/src/chai3d.h"
#include <GLFW/glfw3.h>

using namespace chai3d;
using namespace std;

#include "CBullet.h"

//Game clock
extern cPrecisionClock gameTimer;


//variable for storing time when paused
extern double timecount;

//Holds the time after pausing 
extern double countFrom;

//resumes clock after pause
void resumeGameClock();

//shows clock counting
void updateClock();

//start the clock at the beggining of the game
void startGameClock();

//Pauses game clock
void pauseGameClock();

//Dtop the game clock
void endClock();