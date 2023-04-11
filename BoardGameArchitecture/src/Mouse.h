#ifndef MOUSE_H
#define MOUSE_H

#include "chai3d.h"
#include <GLFW/glfw3.h>

using namespace chai3d;
using namespace std;


// mouse states
enum MouseState
{
    MOUSE_IDLE,
    MOUSE_SELECTION
};

// position of mouse click.
extern cVector3d selectedPoint;

// mouse position
extern double mouseX, mouseY;

// mouse state
extern MouseState mouseState;


//------------------------------------------------------------------------------
// DECLARED FUNCTIONS
//------------------------------------------------------------------------------

/**
 * @brief callback to handle mouse click
 * 
 * @note when mouse button is clicked, the global variable `selectedPoint` will record the 
 *     closest point in the world compared to the world.
 * 
 * @param a_window 
 * @param a_button 
 * @param a_action 
 * @param a_mods 
 */
void mouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods);

/**
 * @brief callback to handle mouse motion
 * 
 * @param a_window 
 * @param a_posX 
 * @param a_posY 
 */
void mouseMotionCallback(GLFWwindow* a_window, double a_posX, double a_posY);


#endif // MOUSE_H
