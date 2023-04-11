//Include main framework headers and namespaces
#include "chai3d.h"
#include <GLFW/glfw3.h>

using namespace chai3d;
using namespace std;

//Include header for BULLET physics engine
#include "CBullet.h"

//GENERAL SETTINGS

//stereo mode
cStereoMode stereoMode = C_STEREO_DISABLED;   

//fullscreen mode           
bool fullscreen = false;   

// a camera to render the world in the window display
cCamera* camera;        

// a light source to illuminate the objects in the world
cSpotLight *light;                       

// a haptic device handler
cHapticDeviceHandler* handler; 

// a pointer to the current haptic device
shared_ptr<cGenericHapticDevice> hapticDevice;  

// a virtual tool representing the haptic device in the scene
cGenericTool* tool;        

// a label to display the rates [Hz] at which the simulation is running
cLabel* labelRates;  

// a label to display information about the controller
cLabel* labelInfo;                                         
 
//BULLET MODULE VARIABLES
cBulletWorld* bulletWorld;
//--------------------------------------------------------------
//ctrlf manually set
#include "Obstacle.h"

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
cBulletBox* bulletObstacleTestBorder1;
cBulletBox* bulletObstacleTestBorder2;
cBulletBox* bulletObstacleTestBorder3;
cBulletBox* bulletObstacleTestBorder4;
cBulletBox* bulletObstacleTestPurple;
cBulletBox* bulletObstacleTestBlue;
cBulletBox* bulletObstacleTestGreen;
cBulletBox* bulletObstacleTestRed;

cBulletStaticPlane* bulletInvisibleWall1;
cBulletStaticPlane* bulletInvisibleWall2;
cBulletStaticPlane* bulletInvisibleWall3;
cBulletStaticPlane* bulletInvisibleWall4;
cBulletStaticPlane* bulletInvisibleWall5;
cBulletStaticPlane* bulletGround;

double mouseX, mouseY;
double prevMouseX;
double prevMouseY;

cMaterial material;

btHingeConstraint* hinge0;
btHingeConstraint* hinge1;

cPanel* panel;
cLabel* labelMousePos;
cLabel* labelBoardAngleX;
cLabel* labelBoardAngleY;
double angleX; //doesnt work
double angleY;

cLabel* clockInfo;
double timeCount;
cPrecisionClock gameTimer;
bool gameStarted = false;
bool gamePaused = false;
double countFrom = 0;
cPanel* pausePanel;
cPanel* startPanel;
cLabel* labelStart;
cLabel* labelOptions;
cLabel* labelExit;
cLabel* labelExit2;
cLabel* labelResume;
cPanel* rpanel;

cBulletMultiMesh* gameBoard;

string resourceRoot;
#define RESOURCE_PATH(p)    (char*)((resourceRoot+string(p)).c_str())
//--------------------------------------------------------------

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
void mouseMotionCallback(GLFWwindow* a_window, double a_posX, double a_posY);           //ctrlf manually added
void mouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods); //ctrlf manually added
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

    camera->set(cVector3d (0, -2.5, 3),    // camera position (eye)(1.25, -2.5, 1.5)
                cVector3d (0, 0, 0.0),    // lookat position (target)(1.25, 1.25, 0.0)
                cVector3d (0.0, 0.0, 1.0));   // direction of the "up" vector

    camera->setClippingPlanes(0.01, 10.0);
    camera->setStereoMode(stereoMode);
    camera->setStereoEyeSeparation(0.02);
    camera->setStereoFocalLength(2.0);
    
    light = new cSpotLight(bulletWorld);
    bulletWorld->addChild(light);
    light->setEnabled(true);
    light->setLocalPos(0, 0.0, 1.5); //(1.25, 1.25, 2);
    light->setDir(0.0, 0.0, -1.0);
    light->setSpotExponent(0.0);
    light->setShadowMapEnabled(true);
    light->m_shadowMap->setQualityMedium();
    light->setCutOffAngleDeg(180); //45

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

    bulletWorld->addChild(tool); //add tool sphere to world
    tool->setDeviceGlobalPos(cVector3d(0,0,5)); //ctrlf TOOL INITIAL POSITION     
    tool->setHapticDevice(hapticDevice);
    tool->setWorkspaceRadius(1.3);
    double toolRadius = 0.06;
    tool->setRadius(toolRadius, toolRadius);
    tool->enableDynamicObjects(true);
    tool->setWaitForSmallForce(true);
    tool->start();

    //WIDGETS
    cFontPtr font = NEW_CFONTCALIBRI20();
    cFontPtr fontStart = NEW_CFONTCALIBRI72();

    labelRates = new cLabel(font);
    labelRates->m_fontColor.setBlack();
    camera->m_frontLayer->addChild(labelRates);

    labelInfo = new cLabel(font);
    labelInfo->m_fontColor.setBlack();
    camera->m_frontLayer->addChild(labelInfo);

//-----------------------------------------------------------------------------------------------------
    panel = new cPanel();
    camera->m_frontLayer->addChild(panel);
    panel->setSize(150, 100);
    panel->m_material->setGrayDim();
    panel->setTransparencyLevel(0.8);

    labelMousePos = new cLabel(font);
    panel->addChild(labelMousePos);
    labelMousePos->setLocalPos(15, 10, 0.1);
    labelMousePos->m_fontColor.setWhite();

    //DOESNT WORK
    // labelBoardAngleY = new cLabel(font);
    // panel->addChild(labelBoardAngleY);
    // labelBoardAngleY->setLocalPos(15, 30, 0.1);
    // labelBoardAngleY->m_fontColor.setWhite();

    // labelBoardAngleX = new cLabel(font);
    // panel->addChild(labelBoardAngleX);
    // labelBoardAngleX->setLocalPos(15, 50, 0.1);
    // labelBoardAngleX->m_fontColor.setWhite();

    clockInfo = new cLabel(font);
    panel->addChild(clockInfo);
    clockInfo->m_fontColor.setWhite();
    clockInfo->setLocalPos(15, 70, 0.1);

    pausePanel = new cPanel();
    pausePanel->setSize(width, height);
    pausePanel->setTransparencyLevel(0.8);

    startPanel = new cPanel();
    camera->m_frontLayer->addChild(startPanel);
    startPanel->setSize(width, height);
    startPanel->setTransparencyLevel(1.0);

    labelStart = new cLabel(fontStart);
    startPanel->addChild(labelStart);
    labelStart->setText("Start");
    labelStart->setLocalPos(width / 6 , (height/2) + 50, 0.1);
    labelStart->m_fontColor.setWhite();

    labelOptions = new cLabel(fontStart);
    startPanel->addChild(labelOptions);
    labelOptions->setText("Options:");
    labelOptions->setLocalPos(0.5 * width , 0.75 * height, 0.1);
    labelOptions->m_fontColor.setWhite();

    labelExit = new cLabel(fontStart);
    startPanel->addChild(labelExit);
    labelExit->setText("Exit");
    labelExit->setLocalPos(width/6, (height/2) - 50, 0.1);
    labelExit->m_fontColor.setWhite();

    labelExit2 = new cLabel(font);
    pausePanel->addChild(labelExit2);
    labelExit2->setText("Exit");
    labelExit2->setLocalPos(width/2, (height/2), 0.1);
    labelExit2->m_fontColor.setWhite();

    labelResume = new cLabel(font);
    pausePanel->addChild(labelResume);
    labelResume->setText("Reesume");
    labelResume->setLocalPos(width/2, (height/2) + 50, 0.1);
    labelResume->m_fontColor.setWhite();

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------

    //ctrlf

    double workspaceScaleFactor = tool->getWorkspaceScaleFactor();
    double maxStiffness	= hapticDeviceInfo.m_maxLinearStiffness / workspaceScaleFactor;
    bulletWorld->setGravity(0.0, 0.0,-9.8);

    //cMaterial material;
    material.setRedFireBrick();
    material.setStiffness(0.3 * maxStiffness);
    material.setDynamicFriction(0.9);
    material.setStaticFriction(0.9);

    double boardSize = 2.5;

    bulletBoard = new cBulletBox(bulletWorld, boardSize, boardSize, 0.05);
    bulletWorld->addChild(bulletBoard);
    bulletBoard->setMaterial(material);
    bulletBoard->buildDynamicModel();
    bulletBoard->createAABBCollisionDetector(toolRadius);
    bulletBoard->setLocalPos(0, 0, 0.0); //(1.25, 1.25, 0.0)

    material.setBlueAquamarine();
    bulletBall = new cBulletSphere(bulletWorld, 0.02);  
    bulletWorld->addChild(bulletBall);
    bulletBall->setMaterial(material);
    bulletBall->setMass(0.5);
    bulletBall->estimateInertia();
    bulletBall->buildDynamicModel();
    bulletBall->createAABBCollisionDetector(toolRadius);
    bulletBall->setLocalPos(0.5,0, 1.5); //(1.25, 1.5, 1.0);

//----------------------------------------------

    //-----------------------------------------------------------------------------------------------------
    // gameBoard = new cBulletMultiMesh(bulletWorld);
    // bulletWorld->addChild(gameBoard);

    // // load model
    // bool fileload;
    // fileload = gameBoard->loadFromFile(RESOURCE_PATH("level1.3ds"));
    // // if (!fileload)
    // // {
    // //     cout << "error" << endl;
    // //     #if defined(_MSVC)
    // //     fileload = gameBoard->loadFromFile("../../../Desktop/GameBoard.3ds");
    // //     #endif
    // // }

    // // scale model
    // gameBoard->scale(0.005);
    // gameBoard->buildContactTriangles(0.001);     // create collision model
    // gameBoard->setMaterial(material);

    // gameBoard->createAABBCollisionDetector(toolRadius);

    // // create dynamic models
    // gameBoard->buildDynamicModel();
    
    // // set position
    // gameBoard->setLocalPos(-1, -1,0);
//-------------------------------------------------------------------
    Obstacle* test0 = new Obstacle(bulletWorld, bulletBoard, boardSize, 0.1, 0.5, 0.0,              -boardSize / 2,     0.0);
    Obstacle* test1 = new Obstacle(bulletWorld, bulletBoard, boardSize, 0.1, 0.5, 0.0,              boardSize / 2,      0.0);
    Obstacle* test2 = new Obstacle(bulletWorld, bulletBoard, boardSize, 0.1, 0.5, boardSize / 2,    0.0,                0.0);
    //test2->rotateAboutGlobalAxisDeg(cVector3d(0, 0, 1.0), 90);
    Obstacle* test3 = new Obstacle(bulletWorld, bulletBoard, boardSize, 0.1, 0.5, -boardSize / 2,   0.0,                0.0);
    //test3->rotateAboutGlobalAxisDeg(cVector3d(0, 0, 1.0), 90);
    
    
    // bulletObstacleTestBorder1 = new cBulletBox(bulletWorld, boardSize, 0.1, 0.5);
    // bulletBoard->addChild(bulletObstacleTestBorder1);
    // material.setYellowGold();
    // bulletObstacleTestBorder1->setMaterial(material);
    // bulletObstacleTestBorder1->buildDynamicModel();
    // bulletObstacleTestBorder1->createAABBCollisionDetector(toolRadius);
    // bulletObstacleTestBorder1->setLocalPos(0.0, -boardSize / 2, 0.0);

    // bulletObstacleTestBorder2 = new cBulletBox(bulletWorld, boardSize, 0.1, 0.5);
    // bulletBoard->addChild(bulletObstacleTestBorder2);
    // material.setYellowGold();
    // bulletObstacleTestBorder2->setMaterial(material);
    // bulletObstacleTestBorder2->buildDynamicModel();
    // bulletObstacleTestBorder2->createAABBCollisionDetector(toolRadius);
    // bulletObstacleTestBorder2->setLocalPos(0.0, boardSize / 2, 0.0);

    // bulletObstacleTestBorder3 = new cBulletBox(bulletWorld, boardSize, 0.1, 0.5);
    // bulletBoard->addChild(bulletObstacleTestBorder3);
    // material.setYellowGold();
    // bulletObstacleTestBorder3->setMaterial(material);
    // bulletObstacleTestBorder3->buildDynamicModel();
    // bulletObstacleTestBorder3->createAABBCollisionDetector(toolRadius);
    // bulletObstacleTestBorder3->setLocalPos(boardSize / 2, 0.0, 0.0);
    // bulletObstacleTestBorder3->rotateAboutGlobalAxisDeg(cVector3d(0, 0, 1.0), 90);

    // bulletObstacleTestBorder4 = new cBulletBox(bulletWorld, boardSize, 0.1, 0.5);
    // bulletBoard->addChild(bulletObstacleTestBorder4);
    // material.setYellowGold();
    // bulletObstacleTestBorder4->setMaterial(material);
    // bulletObstacleTestBorder4->buildDynamicModel();
    // bulletObstacleTestBorder4->createAABBCollisionDetector(toolRadius);
    // bulletObstacleTestBorder4->setLocalPos(-boardSize / 2, 0.0, 0.0);
    // bulletObstacleTestBorder4->rotateAboutGlobalAxisDeg(cVector3d(0, 0, 1.0), 90);

    // bulletObstacleTestPurple = new cBulletBox(bulletWorld, 0.1, 0.1, 1.0);
    // bulletBoard->addChild(bulletObstacleTestPurple);
    // material.setPurpleAmethyst();
    // bulletObstacleTestPurple->setMaterial(material);
    // bulletObstacleTestPurple->buildDynamicModel();
    // bulletObstacleTestPurple->createAABBCollisionDetector(toolRadius);
    // bulletObstacleTestPurple->setLocalPos(-boardSize / 2, -boardSize / 2, 0.0);

    // bulletObstacleTestBlue = new cBulletBox(bulletWorld, 0.1, 0.1, 1.0);
    // bulletBoard->addChild(bulletObstacleTestBlue);
    // material.setBlueDeepSky();
    // bulletObstacleTestBlue->setMaterial(material);
    // bulletObstacleTestBlue->buildDynamicModel();
    // bulletObstacleTestBlue->createAABBCollisionDetector(toolRadius);
    // bulletObstacleTestBlue->setLocalPos(boardSize / 2, boardSize / 2, 0.0);

    // bulletObstacleTestGreen = new cBulletBox(bulletWorld, 0.1, 0.1, 1.0);
    // bulletBoard->addChild(bulletObstacleTestGreen);
    // material.setGreenMediumAquamarine();
    // bulletObstacleTestGreen->setMaterial(material);
    // bulletObstacleTestGreen->buildDynamicModel();
    // bulletObstacleTestGreen->createAABBCollisionDetector(toolRadius);
    // bulletObstacleTestGreen->setLocalPos(boardSize / 2, -boardSize / 2, 0.0);

    // bulletObstacleTestRed = new cBulletBox(bulletWorld, 0.1, 0.1, 1.0);
    // bulletBoard->addChild(bulletObstacleTestRed);
    // material.setRedLightSalmon();
    // bulletObstacleTestRed->setMaterial(material);
    // bulletObstacleTestRed->buildDynamicModel();
    // bulletObstacleTestRed->createAABBCollisionDetector(toolRadius);
    // bulletObstacleTestRed->setLocalPos(-boardSize / 2, boardSize / 2, 0.0);
//-------------------------------------------------------------------
    double planeWidth = 1;
    bulletInvisibleWall1 = new cBulletStaticPlane(bulletWorld, cVector3d(0.0, 0.0, -1.0), -2.0 * planeWidth);
    bulletInvisibleWall2 = new cBulletStaticPlane(bulletWorld, cVector3d(0.0, -1.0, 0.0), -planeWidth);
    bulletInvisibleWall3 = new cBulletStaticPlane(bulletWorld, cVector3d(0.0, 1.0, 0.0), -planeWidth);
    bulletInvisibleWall4 = new cBulletStaticPlane(bulletWorld, cVector3d(-1.0, 0.0, 0.0), -planeWidth);
    bulletInvisibleWall5 = new cBulletStaticPlane(bulletWorld, cVector3d(1.0, 0.0, 0.0), -0.8 * planeWidth);

    bulletGround = new cBulletStaticPlane(bulletWorld, cVector3d(0.0, 0.0, 1.0), -planeWidth);
    bulletWorld->addChild(bulletGround);
    cCreatePlane(bulletGround, 3.0, 3.0, bulletGround->getPlaneConstant() * bulletGround->getPlaneNormal());
    cMaterial matGround;
    matGround.setStiffness(0.3 * maxStiffness);
    matGround.setDynamicFriction(0.2);
    matGround.setStaticFriction(0.0);
    matGround.setPurpleMediumSlateBlue();
    matGround.m_emission.setGrayLevel(0.3);
    bulletGround->setMaterial(matGround);
    bulletGround->createAABBCollisionDetector(toolRadius);
    bulletGround->setSurfaceFriction(0.4);


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
    prevMouseX = mouseX;
    prevMouseY = mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    if ((a_action != GLFW_PRESS) && (a_action != GLFW_REPEAT))
    {
        return;
    }

    else if ((a_key == GLFW_KEY_ESCAPE) || (a_key == GLFW_KEY_Q))
    {
        glfwSetWindowShouldClose(a_window, GLFW_TRUE);
    }

    else if (a_key == GLFW_KEY_W)
    {
        cVector3d norm1(-0.1, 0, 0); //x y z
        bulletBoard->rotateAboutGlobalAxisDeg(norm1, 1);
        angleY++;
    }
    else if (a_key == GLFW_KEY_A)
    {
        cVector3d norm1(0.0, -0.1, 0); //x y z
        bulletBoard->rotateAboutGlobalAxisDeg(norm1, 1);
        angleX--;
    }
    else if (a_key == GLFW_KEY_S)
    {
        cVector3d norm1(0.1, 0, 0); //x y z
        bulletBoard->rotateAboutGlobalAxisDeg(norm1, 1);
        angleY--;
    }
    else if (a_key == GLFW_KEY_D)
    {
        cVector3d norm1(0.0, 0.1, 0); //x y z
        bulletBoard->rotateAboutGlobalAxisDeg(norm1, 1);
        angleX++;
    }
    else if (a_key == GLFW_KEY_X)
    {   
        cout << "local: ";
        bulletObstacleTestBorder1->setLocalPos(0.5, 0, 0.1);

        //bulletObstacleTestBorder1->rotateAboutLocalAxisDeg(cVector3d(1,-1,0), 5);
        cout << bulletObstacleTestBorder1->getLocalPos().x() << ", ";
        cout << bulletObstacleTestBorder1->getLocalPos().y() << ", ";
        cout << bulletObstacleTestBorder1->getLocalPos().z() << " " << endl;
    }
    else if (a_key == GLFW_KEY_C)
    {   cout << "global: ";
        cout << bulletObstacleTestBorder1->getGlobalPos().x() << ", ";
        cout << bulletObstacleTestBorder1->getGlobalPos().y() << ", ";
        cout << bulletObstacleTestBorder1->getGlobalPos().z() << " " << endl;
    }
    else if (a_key == GLFW_KEY_B)
    {   
        bulletBoard->setTransparencyLevel(0);
    }
    else if (a_key == GLFW_KEY_P)
    {
        if (gameStarted){
            if(gamePaused == false){
           
                camera->m_frontLayer->addChild(pausePanel); 
                countFrom = gameTimer.stop();
                gamePaused = true;
            }
       
            else if (gamePaused){
           
                camera->m_frontLayer->removeChild(pausePanel);
                //gameTimer->start(false);
                gameTimer.reset(countFrom);
                gameTimer.start();
                gamePaused = false;
            }
        }
       
    }



    else if (a_key == GLFW_KEY_F)
    {
        // toggle state variable
        fullscreen = !fullscreen;

        // get handle to monitor
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
        prevMouseX = mouseX;
        prevMouseY = mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        cVector3d norm1((mouseY - prevMouseY), (mouseX - prevMouseX), 0); //x y z
        bulletBoard->rotateAboutGlobalAxisDeg(norm1, 1);
        // gameBoard->rotateAboutGlobalAxisDeg(norm1, 1);
        //This doesn't work
        // if ((mouseX - prevMouseX) > 0)
        //     angleX++;
        // else
        //     angleX--;
        // if((mouseY - prevMouseY) > 0)
        //     angleY++;
        // else
        //     angleY--;
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
            if (recorder.m_nearestCollision.m_object == labelStart )
            {
                camera->m_frontLayer->removeChild(startPanel);
                gameTimer.start();
                gameStarted = true;
            }
            else if (recorder.m_nearestCollision.m_object == labelResume )
            {
                gamePaused = false;
                camera->m_frontLayer->removeChild(pausePanel);
                //gameTimer.start(false);
                gameTimer.reset(countFrom);
                gameTimer.start();
                 
            }
            else if (recorder.m_nearestCollision.m_object == labelExit )
            {
                glfwSetWindowShouldClose(a_window, GLFW_TRUE);
            }
            else if (recorder.m_nearestCollision.m_object == labelExit2 )
            {
                glfwSetWindowShouldClose(a_window, GLFW_TRUE);
            }


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
    //ctrlf
    // bulletObstacleTestBorder1->rotateAboutLocalAxisDeg(cVector3d(1,-1,0), 5);
    //bulletObstacleTestBorder1->setLocalPos(bulletObstacleTestBorder1->getLocalPos());
    //setGlobalPos(0.5, 0, 0.3);
    //bulletObstacleTestBorder1->buildDynamicModel();
    //bulletObstacleTestBorder1->createAABBCollisionDetector(0.06);
    glfwGetCursorPos(window, &mouseX, &mouseY);
    labelMousePos->setText(cStr(mouseX, 0) + ", " + cStr(mouseY, 0)); //ctrlf label

    timeCount = gameTimer.getCurrentTimeSeconds();
    string sTimecount = cStr(timeCount,2);
    clockInfo->setText("Current Time: " + sTimecount );

    // This doesn't work
    // labelBoardAngleX->setText("angle X: " + cStr(angleX, 0));
    // labelBoardAngleY->setText("angle Y: " + cStr(angleY, 0));

    labelRates->setText(cStr(freqCounterGraphics.getFrequency(), 0) + " Hz / " +
        cStr(freqCounterHaptics.getFrequency(), 0) + " Hz");

    labelRates->setLocalPos((int)(0.5 * (width - labelRates->getWidth())), 15);
    
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