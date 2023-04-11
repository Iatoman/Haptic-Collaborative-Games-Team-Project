#include "Mouse.h"
#include "World.h"
#include "Interface.h"
#include "Config.h"

using namespace chai3d;
using namespace std;

// position of mouse click (initialised to zero)
cVector3d selectedPoint = cVector3d(0, 0, 0);

// mouse position
double mouseX, mouseY;

// mouse state
MouseState mouseState = MOUSE_IDLE;

cGenericObject *selectedObject = NULL;

cVector3d selectedObjectOffset;

/**
 * @brief do something when mouse button is pressed
 *
 * @param a_window
 * @param a_button
 * @param a_action
 * @param a_mods
 */
void mouseButtonCallback(GLFWwindow *a_window, int a_button, int a_action, int a_mods)
{
    if (a_button == GLFW_MOUSE_BUTTON_LEFT && a_action == GLFW_PRESS)
    {
        // store mouse position
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // variable for storing collision information
        cCollisionRecorder recorder;
        cCollisionSettings settings;

        // detect for any collision between mouse and front layer widgets
        bool hit = camera->selectFrontLayer(mouseX, (height - mouseY), width, height, recorder, settings);
        if (hit)
        {
            // psyia3
            // Start Menu
            if (recorder.m_nearestCollision.m_object == startButton)
            {
                camera->m_frontLayer->removeChild(startScreenPanel); // When start button is pushed rm start screen
                startGameClock();
            }
            else if (recorder.m_nearestCollision.m_object == exitButtonss)
            {
                glfwSetWindowShouldClose(a_window, GLFW_TRUE); // If exit is clicked, close the window
            }
            else if (recorder.m_nearestCollision.m_object == exitButtonss)
            {
                glfwSetWindowShouldClose(a_window, GLFW_TRUE); // If exit is clicked, close the window
            }
            else if (recorder.m_nearestCollision.m_object == exitcs)
            {
                glfwSetWindowShouldClose(a_window, GLFW_TRUE); // If exit is clicked, close the window
            }
           
            else if (recorder.m_nearestCollision.m_object == resumeButton)
            {
                paused = false;
                camera->m_frontLayer->removeChild(pauseScreenPanel);
                resumeGameClock();
            }
            else if (recorder.m_nearestCollision.m_object == exitButtonps)
            {
                glfwSetWindowShouldClose(a_window, GLFW_TRUE);
            }
            if (recorder.m_nearestCollision.m_object == displayButton)
            {
                if (darkMode == true)
                {
                    lightBackground();
                }
                else
                {
                    darkBackground();
                }
            }
        }
        else
        {
            // detect for any collision between mouse and world
            bool hit = camera->selectWorld(mouseX, (height - mouseY), width, height, recorder, settings);
            if (hit)
            {
                selectedPoint = recorder.m_nearestCollision.m_globalPos;
                selectedObject = recorder.m_nearestCollision.m_object;
                selectedObjectOffset = recorder.m_nearestCollision.m_globalPos - selectedObject->getLocalPos();
                mouseState = MOUSE_SELECTION;

                // test
                cout << "x: " << selectedPoint.x() << " y: " << selectedPoint.y() << endl;
            }
        }
    }
    else
    {
        mouseState = MOUSE_IDLE;
    }
}

void mouseMotionCallback(GLFWwindow *a_window, double a_posX, double a_posY)
{
 
}
