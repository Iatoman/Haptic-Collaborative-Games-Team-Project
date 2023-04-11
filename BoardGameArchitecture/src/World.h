#ifndef WORLD_H
#define WORLD_H

#include "chai3d.h"
#include <GLFW/glfw3.h>
using namespace chai3d;
using namespace std;

#include "CBullet.h"

    
// stereo Mode
/*
    C_STEREO_DISABLED:            Stereo is disabled 
    C_STEREO_ACTIVE:              Active stereo for OpenGL NVDIA QUADRO cards
    C_STEREO_PASSIVE_LEFT_RIGHT:  Passive stereo where L/R images are rendered next to each other
    C_STEREO_PASSIVE_TOP_BOTTOM:  Passive stereo where L/R images are rendered above each other
*/
extern cStereoMode stereoMode;

// game window
extern GLFWwindow* window;

// width of window
extern int width;

// height of window
extern int height;

// frequency counter to measure the simulation graphic rate
extern cFrequencyCounter freqCounterGraphics;

// mirrored display
extern bool mirroredDisplay;

// swap interval for the display context (vertical synchronization)
extern int swapInterval;

// flag for using damping (ON/OFF)
extern bool useDamping;

// flag for using force field (ON/OFF)
extern bool useForceField;

// fullscreen mode
extern bool fullscreen;

// world that contains all objects of the virtual environment
extern cBulletWorld* world;

// camera to render the world in the window display
extern cCamera* camera;

// light source to illuminate the objects in the world
extern cSpotLight* light;

// haptic thread
extern cThread* hapticsThread;

// bullet ball
extern cBulletSphere *ball;

// check if game finished
extern int gameFinished;

//initialises the world and all its default settings
void initWorld();

// change camera angle to a different set of vectors
void changeCameraPosition(cCamera* camera, cVector3d cameraPos, cVector3d lookatPos, cVector3d upVector);

// change position of the light
void changeLightPosition(cVector3d newLightPosition);

// change direction of the light
void changeLightDirection(cVector3d newLightDirection);

// change gravity of the world
void changeGravity(cVector3d newGravity);

// sets up the game window
void setupWindow();

// runs main graphics loop for the game
void runMainGraphicsLoop();

// updates graphics of the game
void updateGraphics();

// changes background color of the world
void changeBackgroundColor(cBulletWorld* world1);

// callback when a key is pressed
void keyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods);

// callback when the window display is resized
void windowSizeCallback(GLFWwindow* a_window, int a_width, int a_height);


// handles errors caused within the game
void errorCallback(int a_error, const char* a_description);

// deletes resources and terminates the game
void close();

#endif
