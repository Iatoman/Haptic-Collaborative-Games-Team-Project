#include "World.h"
#include "Mouse.h"
#include "Interface.h"
#include "Ball.h"
#include "Haptic.h"
#include "Config.h"
#include "Game.h"

// stereo Mode
/*
    C_STEREO_DISABLED:            Stereo is disabled
    C_STEREO_ACTIVE:              Active stereo for OpenGL NVDIA QUADRO cards
    C_STEREO_PASSIVE_LEFT_RIGHT:  Passive stereo where L/R images are rendered next to each other
    C_STEREO_PASSIVE_TOP_BOTTOM:  Passive stereo where L/R images are rendered above each other
*/
cStereoMode stereoMode = C_STEREO_DISABLED;

// game window
GLFWwindow *window = NULL;

// width of window
int width = 0;

// height of window
int height = 0;

// frequency counter to measure the simulation graphic rate
cFrequencyCounter freqCounterGraphics;

// mirrored display
bool mirroredDisplay = false;

// swap interval for the display context (vertical synchronization)
int swapInterval = 1;

// flag for using damping (ON/OFF)
bool useDamping = false;

// flag for using force field (ON/OFF)
bool useForceField = true;

// fullscreen mode
bool fullscreen = false;

// checks if game finished or not
int gameFinished = 0;

// world that contains all objects of the virtual environment
cBulletWorld *world;

// camera to render the world in the window display
cCamera *camera;

// light source to illuminate the objects in the world
cSpotLight *light;

// haptic thread
cThread *hapticsThread;

// bullet ball
cBulletSphere *ball;

/**
 * @brief Handles errors within the game
 * 
 * @param a_error The error caused
 * @param a_description Description of the error
 */
void errorCallback(int a_error, const char *a_description)
{
    cout << "Error: " << a_description << endl;
}

/**
 * @brief Initialises the world by setting it up and adding the appropriate cameras and lighting into it 
 * 
 */
void initWorld()
{

    setupWindow();
    
    // create a new world.
    world = new cBulletWorld();

    // set the background color of the environment to white
    world->m_backgroundColor.setWhite();

    // create a camera and insert it into the virtual world
    camera = new cCamera(world);

    world->addChild(camera);

    camera->set(cVector3d(2.5, 0, 2.5),  // camera position (eye)
                cVector3d(0.0, 0.0, 0.0), // lookat position (target)
                cVector3d(0.0, 0.0, 1.0));

    // set the near and far clipping planes of the camera
    // anything in front or behind these clipping planes will not be rendered
    camera->setClippingPlanes(0.01, 10.0);

    // set stereo mode
    camera->setStereoMode(stereoMode);

    // set stereo eye separation and focal length (applies only if stereo is enabled)
    camera->setStereoEyeSeparation(0.02);
    camera->setStereoFocalLength(2.0);

    // set vertical mirrored display mode
    camera->setMirrorVertical(mirroredDisplay);

    // create a light source
    light = new cSpotLight(world);

    // attach light to camera
    world->addChild(light);

    // enable light source
    light->setEnabled(true);

    // position the light source
    // light->setLocalPos(1.25, 1.25, 0.5);
    light->setLocalPos(0.0, 0.0, 3.2);

    // define the direction of the light beam
    light->setDir(0.0, 0.0, -1.0);

    // enable this light source to generate shadows
    light->setShadowMapEnabled(true);

    // set the resolution of the shadow map
    // light->m_shadowMap->setQualityLow();
    light->m_shadowMap->setQualityMedium();

    // set light cone half angle
    light->setCutOffAngleDeg(45);

    changeGravity(cVector3d(0, 0, -9.81));
}

/**
 * @brief Changes the position of the camera being used 
 * 
 * @param camera The camera to change the position of
 * @param cameraPos The new position of the camera
 * @param lookatPos The new coordinates for the camera to look at
 * @param upVector Direction of the (up) vector
 */
void changeCameraPosition(cCamera* camera, cVector3d cameraPos, cVector3d lookatPos, cVector3d upVector)
{
    camera->set(cameraPos, lookatPos, upVector);
}

/**
 * @brief Chnages the position of the light being used
 * 
 * @param newLightPosition The new position of the light
 */
void changeLightPosition(cVector3d newLightPosition)
{
    light->setLocalPos(newLightPosition);
}

/**
 * @brief Changes the background color of the world to black
 * 
 * @param world1 The world whiches colour needs to be changed
 */
void changeBackgroundColor(cBulletWorld* world1)
{
    world1->m_backgroundColor.setBlack();
}

/**
 * @brief Change the direction the light is facing towards
 * 
 * @param newLightDirection  The new direction of the light
 */
void changeLightDirection(cVector3d newLightDirection)
{
    light->setDir(newLightDirection);
}

/**
 * @brief Change the gravity of the world
 * 
 * @param newGravity The new gravity of the world
 */
void changeGravity(cVector3d newGravity)
{
    world->setGravity(newGravity);
}

/**
 * @brief Sets up the window to display the game in.
 * 
 */
void setupWindow()
{

    // initialize GLFW library
    if (!glfwInit())
    {
        cout << "failed initialization" << endl;
        cSleepMs(1000);
        return;
    }

    // set error callback
    glfwSetErrorCallback(errorCallback);

    // compute desired size of window
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int w = 0.8 * mode->height;
    int h = 0.5 * mode->height;
    int x = 0.5 * (mode->width - w);
    int y = 0.5 * (mode->height - h);

    // set OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // set active stereo mode
    if (stereoMode == C_STEREO_ACTIVE)
    {
        glfwWindowHint(GLFW_STEREO, GL_TRUE);
    }
    else
    {
        glfwWindowHint(GLFW_STEREO, GL_FALSE);
    }

    // create display context
    window = glfwCreateWindow(w, h, "Maze Game", NULL, NULL);

    if (!window)
    {
        cout << "failed to create window" << endl;
        cSleepMs(1000);
        glfwTerminate();
        return;
    }

    // get width and height of window
    glfwGetWindowSize(window, &width, &height);

    // set position of window
    glfwSetWindowPos(window, x, y);

    // set key callback
    glfwSetKeyCallback(window, keyCallback);

    // set resize callback
    glfwSetWindowSizeCallback(window, windowSizeCallback);

    // set current display context
    glfwMakeContextCurrent(window);

    // sets the swap interval for the current display context
    glfwSwapInterval(swapInterval);

    glfwSetCursorPosCallback(window, mouseMotionCallback);
    
    glfwSetMouseButtonCallback(window, mouseButtonCallback); 

    // initialize GLEW library
#ifdef GLEW_VERSION
    if (glewInit() != GLEW_OK)
    {
        cout << "failed to initialize GLEW library" << endl;
        glfwTerminate();
        return;
    }
#endif

    return;
}

/**
 * @brief Runs main graphics loop of the game
 * 
 */
void runMainGraphicsLoop()
{

    hapticsThread = new cThread();
    hapticsThread->start(updateMouse, CTHREAD_PRIORITY_HAPTICS);

    atexit(close);

    windowSizeCallback(window, width, height);

    while (!glfwWindowShouldClose(window))
    {
        //resizeInterfaces();

        // get width and height of window
        glfwGetWindowSize(window, &width, &height);

        resizeInterfaces();

        // render graphics
        updateGraphics();

        // swap buffers
        glfwSwapBuffers(window);

        // process events
        glfwPollEvents();

        // signal frequency counter
        freqCounterGraphics.signal(1);
    }

    // close window
    glfwDestroyWindow(window);

    // terminate GLFW library
    glfwTerminate();
}

/**
 * @brief Updates the graphics of the game
 * 
 */
void updateGraphics()
{
    // update shadow maps (if any)
    world->updateShadowMaps(false, mirroredDisplay);
    // render world
    camera->renderView(width, height);

    //Updates clock
    updateClock();

    // wait until all OpenGL commands are completed
    glFinish();

    // check for any OpenGL errors
    GLenum err;
    err = glGetError();
    if (err != GL_NO_ERROR)
        cout << "Error:  %s\n"
             << gluErrorString(err);

    // check winning condition
    doWinCheck();
}

/**
 * @brief maps certain keys to controls for the game
 * 
 * @param a_window The game window
 * @param a_key The key
 * @param a_scancode 
 * @param a_action The action being conducted (key being pressed)
 * @param a_mods The mods for the key (if any)
 */
void keyCallback(GLFWwindow *a_window, int a_key, int a_scancode, int a_action, int a_mods)
{
    // filter calls that only include a key press
    if ((a_action != GLFW_PRESS) && (a_action != GLFW_REPEAT))
    {
        return;
    }

    // option - exit
    else if ((a_key == GLFW_KEY_ESCAPE) || (a_key == GLFW_KEY_Q))
    {
        glfwSetWindowShouldClose(a_window, GLFW_TRUE);
    }

    // option - enable/disable force field
    else if (a_key == GLFW_KEY_1)
    {
        useForceField = !useForceField;
        if (useForceField)
            cout << "> Enable force field     \r";
        else
            cout << "> Disable force field    \r";
    }

    // option - enable/disable damping
    else if (a_key == GLFW_KEY_2)
    {
        useDamping = !useDamping;
        if (useDamping)
            cout << "> Enable damping         \r";
        else
            cout << "> Disable damping        \r";
    }
    else if (a_key == GLFW_KEY_P)
    {
        if (gameStarted == true)
        {
            if (paused == false)
            {
                camera->m_frontLayer->addChild(pauseScreenPanel);
                pauseGameClock();
            }

            else if (paused == true)
            {
                camera->m_frontLayer->removeChild(pauseScreenPanel);
                resumeGameClock();
                paused = false;
            }
        }
    }
    else if (a_key == GLFW_KEY_G)
    {
        //goalhit = true;
        timecount = gameTimer.stop();
        gameFinished = true;
        createCompletedScreen(timecount, 1);

    }

    // option - toggle fullscreen
    else if (a_key == GLFW_KEY_F)
    {
        // toggle state variable
        fullscreen = !fullscreen;

        // get handle to monitor
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();

        // get information about monitor
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);

        // set fullscreen or window mode
        if (fullscreen)
        {
            glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            glfwSwapInterval(swapInterval);
        }
        else
        {
            int w = 0.8 * mode->height;
            int h = 0.5 * mode->height;
            int x = 0.5 * (mode->width - w);
            int y = 0.5 * (mode->height - h);
            glfwSetWindowMonitor(window, NULL, x, y, w, h, mode->refreshRate);
            glfwSwapInterval(swapInterval);
        }
    }

    // option - toggle vertical mirroring
    else if (a_key == GLFW_KEY_M)
    {
        setBallSpawnPoint(ball, 0.0, 0.0, 2);
        tool->setLocalPos(0,0,2);
    }
}

/**
 * @brief Updates the size of the window
 * 
 * @param a_window The window
 * @param a_width The width of the window
 * @param a_height The height of the window
 */
void windowSizeCallback(GLFWwindow* a_window, int a_width, int a_height)
{
    // update window size
    width = a_width;
    height = a_height;
}

/**
 * @brief Deletes resources and terminates the game
 * 
 */
void close(void)
{
    // stop the simulation
    simulationRunning = false;

    // wait for graphics and haptics loops to terminate
    while (!simulationFinished)
    {
        cSleepMs(100);
    }

    // close haptic device
    // tool->stop();

    // delete resources
    delete hapticsThread;
    delete world;
    // delete handler;
}


