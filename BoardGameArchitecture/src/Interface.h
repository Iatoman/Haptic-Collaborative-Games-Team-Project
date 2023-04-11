#ifndef INTERFACE_H
#define INTERFACE_H


#include "../../chai3d-3.2.0/src/chai3d.h"
#include <GLFW/glfw3.h>

using namespace chai3d;
using namespace std;

//#include "../../chai3d-3.2.0/modules/BULLET/src/CBullet.h"

//Panels for start and pause menus
extern cPanel* startScreenPanel;
extern cPanel* pauseScreenPanel;

//Goal achieved screen panel
extern cPanel* completedScreenPanel;

//Panel that shows the clock
extern cPanel* clockPanel;

//Start screen buttons
extern cLabel* startButton;
extern cLabel* exitButtonss;

//Pause menu buttons
extern cLabel* resumeButton;
extern cLabel* exitButtonps;
extern cLabel* displayButton;

//Completed screen buttons
extern cLabel* nextLevel;
extern cLabel* exitcs;

//Level completed message
extern cLabel* completedMessage;

//Clock message label
extern cLabel* clockInfo;
 
 //Colors for the background
extern cColorf black;
extern cColorf blue;
extern cColorf white;

//fonts for labels
extern cFontPtr font;

//Boolean for when the game starts
extern bool gameStarted;

//Boolean for when game is paused
extern bool paused;

//Checks what mode thr game is in
extern bool darkMode;

//string for resource root
extern string resourceRoot;

//Creates start screen
void createStartscreen();
//Create pause screen
void createPausescreen();
//creates goal screen
void createCompletedScreen(int timetaken, int level);
//Adds clock panel
void clockInterface();

//Changes game to dark/light mode
void darkBackground ();
void lightBackground ();

//Updates interface sizes when window changes
void resizeInterfaces();

#endif //INTERFACE_H
