#include "chai3d.h"
#include <GLFW/glfw3.h>

using namespace chai3d;
using namespace std;

#include "CBullet.h"

//GENERAL SETTINGS
cStereoMode stereoMode = C_STEREO_DISABLED;                 //stereo mode
bool fullscreen = false;                                    //fullscreen mode
bool mirroredDisplay = false;                               //mirrored display
cCamera* camera;                                            // a camera to render the world in the window display
cSpotLight *light;                                          // a light source to illuminate the objects in the world
cHapticDeviceHandler* handler;                              // a haptic device handler
shared_ptr<cGenericHapticDevice> hapticDevice;              // a pointer to the current haptic device
cGenericTool* tool;                                         // a virtual tool representing the haptic device in the scene
cLabel* labelRates;                                         // a label to display the rates [Hz] at which the simulation is running
cLabel* labelInfo;                                          // a label to display information about the controller
 
//BULLET MODULE VARIABLES
cBulletWorld* bulletWorld;
//--------------------------------------------------------------
//ctrlf manually set
enum MouseState
{
    MOUSE_IDLE,
    MOUSE_SELECTION
};

cVector3d selectedPoint;
cGenericObject* selectedObject = NULL;
cVector3d selectedObjectOffset;

MouseState mouseState = MOUSE_IDLE;
cBulletBox* bulletBoard;
cBulletSphere* bulletBall;
cBulletBox* bulletObstacleTest;

double mouseX, mouseY;

//--------------------------------------------------------------
bool controllerEnabled = false;
double angPosDes = 0.0;

//GENERAL VARIABLES
bool simulationRunning = false;
bool simulationFinished = true;
cFrequencyCounter freqCounterGraphics;
cFrequencyCounter freqCounterHaptics;
cThread* hapticsThread;
GLFWwindow* window = NULL;
int width = 0;
int height = 0;
int swapInterval = 1;

//DECLARING FUNCTIONS
void windowSizeCallback(GLFWwindow* a_window, int a_width, int a_height);
void errorCallback(int error, const char* a_description);
void keyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods);
void mouseMotionCallback(GLFWwindow* a_window, double a_posX, double a_posY);
void mouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods);
void updateGraphics(void);
void updateHaptics(void);
void close(void);

int main(int argc, char* argv[])
{
    cout << endl;
    cout << "main" << endl;

    //OPENGL
    if (!glfwInit())
    {
        cout << "failed initialization" << endl;
        cSleepMs(1000);
        return 1;
    }

    glfwSetErrorCallback(errorCallback);

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int w = 0.8 * mode->height;
    int h = 0.5 * mode->height;
    int x = 0.5 * (mode->width - w);
    int y = 0.5 * (mode->height - h);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    if (stereoMode == C_STEREO_ACTIVE)
    {
        glfwWindowHint(GLFW_STEREO, GL_TRUE);
    }
    else
    {
        glfwWindowHint(GLFW_STEREO, GL_FALSE);
    }

    window = glfwCreateWindow(w, h, "CHAI3D", NULL, NULL);
    if (!window)
    {
        cout << "failed to create window" << endl;
        cSleepMs(1000);
        glfwTerminate();
        return 1;
    }

    glfwGetWindowSize(window, &width, &height);
    glfwSetWindowPos(window, x, y);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(swapInterval);
    glfwSetCursorPosCallback(window, mouseMotionCallback); //ctrlf callback
    glfwSetMouseButtonCallback(window, mouseButtonCallback); //ctrlf callback

#ifdef GLEW_VERSION
    if (glewInit() != GLEW_OK)
    {
        cout << "failed to initialize GLEW library" << endl;
        glfwTerminate();
        return 1;
    }
#endif

    //ctrlf WORLD CAMERA LIGHTING
    bulletWorld = new cBulletWorld();
    bulletWorld->m_backgroundColor.setWhite();
    camera = new cCamera(bulletWorld);
    bulletWorld->addChild(camera);

    camera->set(cVector3d (2.5, 0.0, 1.5),    // camera position (eye)
                cVector3d (0.0, 0.0, 0.0),    // lookat position (target)
                cVector3d (0.0, 0.0, 1.0));   // direction of the "up" vector

    camera->setClippingPlanes(0.01, 10.0);
    camera->setStereoMode(stereoMode);
    camera->setStereoEyeSeparation(0.02);
    camera->setStereoFocalLength(2.0);
    camera->setMirrorVertical(mirroredDisplay);
    light = new cSpotLight(bulletWorld);
    bulletWorld->addChild(light);
    light->setEnabled(true);
    light->setLocalPos(1.2, 0.0, 1.2);
    light->setDir(-1.0, 0.0, -1.0);
    light->setSpotExponent(0.0);
    light->setShadowMapEnabled(true);
    light->m_shadowMap->setQualityMedium();
    light->setCutOffAngleDeg(45);

    //HAPTIC DEVICE/TOOLS
    handler = new cHapticDeviceHandler();
    handler->getDevice(hapticDevice, 0);
    cHapticDeviceInfo hapticDeviceInfo = hapticDevice->getSpecifications();

    if (hapticDeviceInfo.m_actuatedGripper)
    {
        tool = new cToolGripper(bulletWorld);
    }
    else
    {
        tool = new cToolCursor(bulletWorld);
    }

    bulletWorld->addChild(tool);
    tool->setHapticDevice(hapticDevice);
    tool->setWorkspaceRadius(1.3);
    double toolRadius = 0.06;
    tool->setRadius(toolRadius, toolRadius);
    tool->enableDynamicObjects(true);
    tool->setWaitForSmallForce(true);
    tool->start();

    //WIDGETS
    cFontPtr font = NEW_CFONTCALIBRI20();

    labelRates = new cLabel(font);
    labelRates->m_fontColor.setBlack();
    camera->m_frontLayer->addChild(labelRates);

    labelInfo = new cLabel(font);
    labelInfo->m_fontColor.setBlack();
    camera->m_frontLayer->addChild(labelInfo);

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------

    //ctrlf

    double workspaceScaleFactor = tool->getWorkspaceScaleFactor();
    double maxStiffness	= hapticDeviceInfo.m_maxLinearStiffness / workspaceScaleFactor;
    bulletWorld->setGravity(0.0, 0.0,-9.8);

    cMaterial material;
    material.setRedFireBrick();
    material.setStiffness(0.3 * maxStiffness);
    material.setDynamicFriction(0.9);
    material.setStaticFriction(0.9);

    bulletBoard = new cBulletBox(bulletWorld, 2.5, 2.5, 0.05);
    bulletWorld->addChild(bulletBoard);
    bulletBoard->setMaterial(material);
    bulletBoard->buildDynamicModel();
    bulletBoard->createAABBCollisionDetector(toolRadius);
    bulletBoard->setLocalPos(0.0, 0.0, 0.0);

    material.setBlueAquamarine();
    bulletBall = new cBulletSphere(bulletWorld, 0.02);  
    bulletWorld->addChild(bulletBall);
    bulletBall->setMaterial(material);
    bulletBall->setMass(0.5);
    bulletBall->estimateInertia();
    bulletBall->buildDynamicModel();
    bulletBall->createAABBCollisionDetector(toolRadius);
    bulletBall->setLocalPos(0.0, 0.0, 1.0);

//----------------------------------------------

    bulletObstacleTest = new cBulletBox(bulletWorld, 0.1, 0.1, 0.5);
    bulletBoard->addChild(bulletObstacleTest);
    material.setYellowGold();
    bulletObstacleTest->setMaterial(material);
    bulletObstacleTest->buildDynamicModel();
    bulletObstacleTest->createAABBCollisionDetector(toolRadius);
    bulletObstacleTest->setLocalPos(1.0, 0.0, 0.0);














    // bulletBox0 = new cBulletBox(bulletWorld, 0.4, 0.1, 0.8);
    // bulletBox1 = new cBulletBox(bulletWorld, 0.4, 0.8, 0.1);

    // bulletWorld->addChild(bulletBox1);
    // bulletBox1->addChild(bulletBox0);

    // cMaterial material;
    // material.setBlueCornflower();
    // material.setStiffness(0.3 * maxStiffness);
    // material.setDynamicFriction(0.6);
    // material.setStaticFriction(0.6);

    // bulletBox0->setMaterial(material);
    // bulletBox1->setMaterial(material);

    // bulletBox0->buildDynamicModel();
    // bulletBox0->createAABBCollisionDetector(toolRadius);
    // bulletBox0->setLocalPos(0.0, -0.8, 0.0);

    // bulletBox1->buildDynamicModel();
    // bulletBox1->createAABBCollisionDetector(toolRadius);
    // bulletBox1->setLocalPos(0.0, 0.0, 0.5);


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------

    hapticsThread = new cThread();                                      // create a thread which starts the main haptics rendering loop
    hapticsThread->start(updateHaptics, CTHREAD_PRIORITY_HAPTICS);
    atexit(close);                                                      // setup callback when application exits

    //ctrlf main loop // MAIN GRAPHIC LOOP
    windowSizeCallback(window, width, height);

    while (!glfwWindowShouldClose(window))
    {
        glfwGetWindowSize(window, &width, &height);                     // get width and height of window
        updateGraphics();                                               // render graphics
        glfwSwapBuffers(window);                                        // swap buffers
        glfwPollEvents();                                               // process events
        freqCounterGraphics.signal(1);                                  // signal frequency counter
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void windowSizeCallback(GLFWwindow* a_window, int a_width, int a_height)
{
    // update window size
    width = a_width;
    height = a_height;
}

void errorCallback(int a_error, const char* a_description)
{
    cout << "Error: " << a_description << endl;
}

void keyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods)
{
    if ((a_action != GLFW_PRESS) && (a_action != GLFW_REPEAT))
    {
        return;
    }

    else if ((a_key == GLFW_KEY_ESCAPE) || (a_key == GLFW_KEY_Q))
    {
        glfwSetWindowShouldClose(a_window, GLFW_TRUE);
    }

    else if (a_key == GLFW_KEY_G)
    {
        if (bulletWorld->getGravity().length() > 0.0)
        {
            bulletWorld->setGravity(cVector3d(0.0, 0.0, 0.0));
        }
        else
        {
            bulletWorld->setGravity(cVector3d(0.0, 0.0, -9.81));
        }
    }

    else if (a_key == GLFW_KEY_C)
    {
        bulletBoard->setLocalPos(0.0, 0.5, 0.0);
    }

    else if (a_key == GLFW_KEY_1)
    {
        angPosDes = cMax(cDegToRad(-90), angPosDes - cDegToRad(5.0));
    }

    else if (a_key == GLFW_KEY_2)
    {
        angPosDes = cMin(cDegToRad(90), angPosDes + cDegToRad(5.0));
    }

    else if (a_key == GLFW_KEY_F)
    {
        // toggle state variable
        fullscreen = !fullscreen;

        // get handle to monitor0.1
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();

        // get information about monitor
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

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
    
    else if (a_key == GLFW_KEY_M)
    {
        mirroredDisplay = !mirroredDisplay;
        camera->setMirrorVertical(mirroredDisplay);
    }
}

void close(void)
{
    // stop the simulation
    simulationRunning = false;

    // wait for graphics and haptics loops to terminate
    while (!simulationFinished) { cSleepMs(100); }

    // close haptic device
    tool->stop();

    // delete resources
    delete hapticsThread;
    delete bulletWorld;
    delete handler;
}

void mouseMotionCallback(GLFWwindow* a_window, double a_posX, double a_posY)
{
    if ((selectedObject != NULL) && (mouseState == MOUSE_SELECTION))
    {
        double prevMouseX = mouseX;
        double prevMouseY = mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        cVector3d norm1(-(mouseX - prevMouseX), (mouseY - prevMouseY), 0); //x y z
        bulletBoard->rotateAboutGlobalAxisRad(norm1, 0.02);
    }
}

//ctrlf comments in 08-ode
void mouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods)
{
    if (a_button == GLFW_MOUSE_BUTTON_LEFT && a_action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &mouseX, &mouseY);
        cCollisionRecorder recorder;
        cCollisionSettings settings;

        bool hit = camera->selectFrontLayer(mouseX, (height - mouseY), width, height, recorder, settings);
        if(hit)
        {
            //placeholder
        }
        else
        {
            bool hit = camera->selectWorld(mouseX, (height - mouseY), width, height, recorder, settings);
            if (hit)
            {
                selectedPoint = recorder.m_nearestCollision.m_globalPos;
                selectedObject = recorder.m_nearestCollision.m_object;
                selectedObjectOffset = recorder.m_nearestCollision.m_globalPos - selectedObject->getLocalPos();
                mouseState = MOUSE_SELECTION;
            }
        }
    }
    else
    {
        mouseState = MOUSE_IDLE;
    }

}

void updateGraphics(void)
{
    labelRates->setText(cStr(freqCounterGraphics.getFrequency(), 0) + " Hz / " +
        cStr(freqCounterHaptics.getFrequency(), 0) + " Hz");

    labelRates->setLocalPos((int)(0.5 * (width - labelRates->getWidth())), 15);

    if (controllerEnabled)
    {
        labelInfo->setText("controller enabled - desired position (deg): " + cStr(cRadToDeg(angPosDes), 0));
    }
    else
    {
        labelInfo->setText("controller disabled - press key 'c' to enable");
    }

    labelInfo->setLocalPos((int)(0.5 * (width - labelInfo->getWidth())), 45);
    bulletWorld->updateShadowMaps(false, mirroredDisplay);
    camera->renderView(width, height);
    glFinish();
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) printf("Error:  %s\n", gluErrorString(err));
}

void updateHaptics(void)
{
    simulationRunning  = true;                      // simulation in now running
    simulationFinished = false;                     // simulation in now running
    cPrecisionClock clock;                          // reset clock
    clock.reset();                                  // reset clock

    while(simulationRunning)
    {
        clock.stop();                               // stop the simulation clock
        double timeInterval = cClamp(clock.getCurrentTimeSeconds(), 0.0001, 0.001); // read the time increment in seconds
        clock.reset();                              // restart the simulation clock
        clock.start();                              // restart the simulation clock
        freqCounterHaptics.signal(1);               // signal frequency counter

        bulletWorld->computeGlobalPositions(true);  // compute global reference frames for each object
        tool->updateFromDevice();                   // update position and orientation of tool
        tool->computeInteractionForces();           // compute interaction forces
        tool->applyToDevice();                      // send forces to haptic device

        bulletWorld->updateDynamics(timeInterval);  // update simulation

        
    }
    simulationFinished = true;
}