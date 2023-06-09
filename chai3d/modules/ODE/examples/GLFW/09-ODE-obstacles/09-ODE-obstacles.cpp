//==============================================================================
/*
    Software License Agreement (BSD License)
    Copyright (c) 2003-2016, CHAI3D.
    (www.chai3d.org)

    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above
    copyright notice, this list of conditions and the following
    disclaimer in the documentation and/or other materials provided
    with the distribution.

    * Neither the name of CHAI3D nor the names of its contributors may
    be used to endorse or promote products derived from this software
    without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE. 

    \author    <http://www.chai3d.org>
    \author    Francois Conti
    \version   3.2.0 $Rev: 1916 $
*/
//==============================================================================
//------------------------------------------------------------------------------
#include "chai3d.h"
#include "CODE.h"

//------------------------------------------------------------------------------
#include <GLFW/glfw3.h>
//------------------------------------------------------------------------------
using namespace chai3d;
using namespace std;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// GENERAL SETTINGS
//------------------------------------------------------------------------------

// stereo Mode
/*
    C_STEREO_DISABLED:            Stereo is disabled 
    C_STEREO_ACTIVE:              Active stereo for OpenGL NVDIA QUADRO cards
    C_STEREO_PASSIVE_LEFT_RIGHT:  Passive stereo where L/R images are rendered next to each other
    C_STEREO_PASSIVE_TOP_BOTTOM:  Passive stereo where L/R images are rendered above each other
*/
cStereoMode stereoMode = C_STEREO_DISABLED;

// fullscreen mode
bool fullscreen = false;

// mirrored display
bool mirroredDisplay = false;


//------------------------------------------------------------------------------
// STATES
//------------------------------------------------------------------------------
enum MouseState
{
    MOUSE_IDLE,
    MOUSE_SELECTION
};


//------------------------------------------------------------------------------
// DECLARED VARIABLES
//------------------------------------------------------------------------------

cODEWorld* ODEWorld;

// ODE objects
cODEGenericBody* ODEBody0;
cODEGenericBody* ODEBody1;
cODEGenericBody* ODEBody2;
cODEGenericBody* ODEBody3;

// ODE objects
cODEGenericBody* ODEGPlane0;
cODEGenericBody* ODEGPlane1;
cODEGenericBody* ODEGPlane2;
cODEGenericBody* ODEGPlane3;
cODEGenericBody* ODEGPlane4;
cODEGenericBody* ODEGPlane5;

//radius and angle from 0,0 for camera movement
double radius = 3.5;
double angle = 0;

// a world that contains all objects of the virtual environment
cWorld* world;

// a camera to render the world in the window display
cCamera* camera;

// a light source to illuminate the objects in the world
cDirectionalLight *light;

// a haptic device handler
cHapticDeviceHandler* handler;

// a pointer to the current haptic device
cGenericHapticDevicePtr hapticDevice;

// a virtual tool representing the haptic device in the scene
cToolCursor* tool;

// some objects
cShapeSphere* sphere;
cShapeBox* box;
cShapeBox* box1;
// a small sphere which displays the position of a click hit in the world
cShapeSphere* sphereSelect;

// a small line to display the surface normal at the selection point
cShapeLine* normalSelect;

// a pointer to the selected object
cGenericObject* selectedObject = NULL;

// offset between the position of the mmouse click on the object and the object reference frame location.
cVector3d selectedObjectOffset;

// position of mouse click.
cVector3d selectedPoint;

// a colored background
cBackground* background;

// a font for rendering text
cFontPtr font;

// a label to display the rate [Hz] at which the simulation is running
cLabel* labelRates;

// a label to explain what is happening
cLabel* labelMessage;

// a widget panel
cPanel* panel;

// some labels
double prevMouseX;
double prevMouseY;
cLabel* labelMousePos;
cLabel* labelRed;
cLabel* labelGreen;
cLabel* labelBlue;
cLabel* labelOrange;
cLabel* labelGray;

// a flag to indicate if the haptic simulation currently running
bool simulationRunning = false;

// a flag to indicate if the haptic simulation has terminated
bool simulationFinished = true;

// mouse position
double mouseX, mouseY;

// mouse state
MouseState mouseState = MOUSE_IDLE;

// a frequency counter to measure the simulation graphic rate
cFrequencyCounter freqCounterGraphics;

// a frequency counter to measure the simulation haptic rate
cFrequencyCounter freqCounterHaptics;

// haptic thread
cThread* hapticsThread;

// a handle to window display context
GLFWwindow* window = NULL;

// current width of window
int width  = 0;

// current height of window
int height = 0;

// swap interval for the display context (vertical synchronization)
int swapInterval = 1;

// root resource path
string resourceRoot;


//------------------------------------------------------------------------------
// DECLARED MACROS
//------------------------------------------------------------------------------
#define RESOURCE_PATH(p)    (char*)((resourceRoot+string(p)).c_str())



//------------------------------------------------------------------------------
// DECLARED FUNCTIONS
//------------------------------------------------------------------------------

// callback when the window display is resized
void windowSizeCallback(GLFWwindow* a_window, int a_width, int a_height);

// callback when an error GLFW occurs
void errorCallback(int error, const char* a_description);

// callback when a key is pressed
void keyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods);

// callback to handle mouse click
void mouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods);

// callback to handle mouse motion
void mouseMotionCallback(GLFWwindow* a_window, double a_posX, double a_posY);

// this function renders the scene
void updateGraphics(void);

// this function contains the main haptics simulation loop
void updateHaptics(void);

// this function closes the application
void close(void);

class Obstacle {
// make && ./../../../bin/lin-x86_64/08-ODE-dan
    public: 

    void initialise (cVector3d one, cVector3d two)
    {
        cODEGenericBody* obstacle;
        obstacle = new cODEGenericBody(ODEWorld);
        //obstacle->createStaticPlane(one, two);

        //cMesh* ground = new cMesh();
        //ODEWorld->addChild(ground);

        //double groundSize = 3.0;
        //cCreatePlane(ground, 2, 2);

        //ground->setLocalPos(two);

        cMaterial matGround;
        matGround.setStiffness(0.3 * 0.0111);
        matGround.setDynamicFriction(0.2);
        matGround.setStaticFriction(0);
        matGround.setBlueAqua();
        matGround.m_emission.setGrayLevel(0.3);
        //ground->setMaterial(matGround);

        //ground->createAABBCollisionDetector(0.01); //toolradius value
    };

};


int main(int argc, char* argv[])
{
    //--------------------------------------------------------------------------
    // INITIALIZATION
    //--------------------------------------------------------------------------

    cout << endl;
    cout << "-----------------------------------" << endl;
    cout << "CHAI3D" << endl;
    cout << "Demo: 07-mouse-select-modify" << endl;
    cout << "Copyright 2003-2016" << endl;
    cout << "-----------------------------------" << endl << endl << endl;
    cout << "Keyboard Options:" << endl << endl;
    cout << "[f] - Enable/Disable full screen mode" << endl;
    cout << "[m] - Enable/Disable vertical mirroring" << endl;
    cout << "[q] - Exit application" << endl;
    cout << endl << endl;


    //--------------------------------------------------------------------------
    // OPEN GL - WINDOW DISPLAY
    //--------------------------------------------------------------------------

    // initialize GLFW library
    if (!glfwInit())
    {
        cout << "failed initialization" << endl;
        cSleepMs(1000);
        return 1;
    }

    // set error callback
    glfwSetErrorCallback(errorCallback);

    // compute desired size of window
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
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
    window = glfwCreateWindow(w, h, "CHAI3D", NULL, NULL);
    if (!window)
    {
        cout << "failed to create window" << endl;
        cSleepMs(1000);
        glfwTerminate();
        return 1;
    }

    // get width and height of window
    glfwGetWindowSize(window, &width, &height);

    // set position of window
    glfwSetWindowPos(window, x, y);

    // set key callback
    glfwSetKeyCallback(window, keyCallback);

    // set resize callback
    glfwSetWindowSizeCallback(window, windowSizeCallback);

    // set mouse position callback
    glfwSetCursorPosCallback(window, mouseMotionCallback);

    // set mouse button callback
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    // set current display context
    glfwMakeContextCurrent(window);

    // sets the swap interval for the current display context
    glfwSwapInterval(swapInterval);

#ifdef GLEW_VERSION
    // initialize GLEW library
    if (glewInit() != GLEW_OK)
    {
        cout << "failed to initialize GLEW library" << endl;
        glfwTerminate();
        return 1;
    }
#endif


    //--------------------------------------------------------------------------
    // WORLD - CAMERA - LIGHTING
    //--------------------------------------------------------------------------

    // create a new world.
    world = new cWorld();

    // set the background color of the environment
    world->m_backgroundColor.setWhite();

    // create a camera and insert it into the virtual world
    camera = new cCamera(world);
    world->addChild(camera);

    // position and orient the camera
    camera->set(cVector3d(3.5 * sin(angle), 3.5 * cos(angle), 1.5),    // camera position (eye) cVector3d(0.8, 0.8, 0.6), 
                cVector3d(0.0, 0.0, 0.0),    // lookat position (target)
                cVector3d(0.0, 0.0, 1.0));   // direction of the (up) vector
    cout << "angle: " << angle << " camerapos: " << camera->getLocalPos() << "\n";

    // set the near and far clipping planes of the camera
    // anything in front or behind these clipping planes will not be rendered
    camera->setClippingPlanes(0.01, 10.0);

    // set stereo mode
    camera->setStereoMode(stereoMode);

    // set stereo eye separation and focal length (applies only if stereo is enabled)
    camera->setStereoEyeSeparation(0.03);
    camera->setStereoFocalLength(1.8);

    // set vertical mirrored display mode
    camera->setMirrorVertical(mirroredDisplay);

    // create a light source
    light = new cDirectionalLight(world);

    // attach light to camera
    camera->addChild(light);

    // enable light source
    light->setEnabled(true);

    // position the light source
    light->setLocalPos(0.0, 0.5, 0.0);

    // define the direction of the light beam
    light->setDir(-2.5,-0.8, 0.0);


    //--------------------------------------------------------------------------
    // HAPTIC DEVICES / TOOLS
    //--------------------------------------------------------------------------

    // create a haptic device handler
    handler = new cHapticDeviceHandler();

    // get access to the first available haptic device
    handler->getDevice(hapticDevice, 0);

    // retrieve information about the current haptic device
    cHapticDeviceInfo hapticDeviceInfo = hapticDevice->getSpecifications();

    // if the haptic devices carries a gripper, enable it to behave like a user switch
    hapticDevice->setEnableGripperUserSwitch(true);

    // create a tool (cursor) and insert into the world
    tool = new cToolCursor(world);
    world->addChild(tool);

    // connect the haptic device to the tool
    tool->setHapticDevice(hapticDevice);

    // map the physical workspace of the haptic device to a larger virtual workspace.
    tool->setWorkspaceRadius(0.9);

    // define the radius of the tool (sphere)
    double toolRadius = 0.01;

    // define a radius for the tool
    tool->setRadius(toolRadius);

    // hide the device sphere. only show proxy.
    tool->setShowContactPoints(true, false);

    // enable if objects in the scene are going to rotate of translate
    // or possibly collide against the tool. If the environment
    // is entirely static, you can set this parameter to "false"
    tool->enableDynamicObjects(true);

    // start the haptic tool
    tool->start();


    //--------------------------------------------------------------------------
    // CREATE OBJECTS
    //--------------------------------------------------------------------------

    // read the scale factor between the physical workspace of the haptic
    // device and the virtual workspace defined for the tool
    double workspaceScaleFactor = tool->getWorkspaceScaleFactor();

    // stiffness properties
    double maxStiffness	= hapticDeviceInfo.m_maxLinearStiffness / workspaceScaleFactor;

    cout << "MaxStiffness: " << maxStiffness << endl;

    // create a small sphere to display a selection hit with the mouse
    sphereSelect = new cShapeSphere(0.005);
    world->addChild(sphereSelect);
    sphereSelect->m_material->setRedCrimson();
    sphereSelect->setShowEnabled(false);
    sphereSelect->setGhostEnabled(true);

    normalSelect = new cShapeLine();
    sphereSelect->addChild(normalSelect);
    normalSelect->m_colorPointA.setRedCrimson();
    normalSelect->m_colorPointB.setRedCrimson();
    normalSelect->setShowEnabled(false);
    normalSelect->setGhostEnabled(true);

    bool fileload;
    sphereSelect->m_texture = cTexture2d::create();
    fileload = sphereSelect->m_texture->loadFromFile(RESOURCE_PATH("../resources/images/spheremap-3.jpg"));
    if (!fileload)
    {
        #if defined(_MSVC)
        fileload = sphereSelect->m_texture->loadFromFile("../../../bin/resources/images/spheremap-3.jpg");
        #endif
    }

    sphereSelect->m_texture->setSphericalMappingEnabled(true);
    sphereSelect->setUseTexture(true);
    sphereSelect->m_material->setWhite();

    
    ////////////////////////////////////////////////////////////////////////////
    // MESH - PRIMITIVE
    ////////////////////////////////////////////////////////////////////////////

    // create a virtual mesh
    //mesh = new cMesh();

    // add object to world
    //world->addChild(mesh);

    // build mesh using a cylinder primitive
    // cCreateCircularArrow(mesh,
    //     0.02,
    //     0.02, 
    //     0.50,
    //     0.10,
    //     0.04,
    //     330,
    //     true,
    //     32,
    //     72,
    //     cVector3d(0,0,1)
    //     );

    // set material color
    //mesh->m_material->setBlueCornflower();

    // set haptic properties
    //mesh->m_material->setStiffness(0.5 * maxStiffness);

    // build collision detection tree
    //mesh->createAABBCollisionDetector(toolRadius);


    ////////////////////////////////////////////////////////////////////////////
    // SHAPE - BOX
    ////////////////////////////////////////////////////////////////////////////

    // box = new cShapeBox(0.08, 0.08, 0.20);
    // world->addChild(box);
    // box->setLocalPos(0.0, 0.0, 0.2);
    // box->createEffectSurface();
    // box->m_material->setStiffness(0.8 * maxStiffness);
    // box->m_material->setGrayLight();


    ////////////////////////////////////////////////////////////////////////////
    // SHAPE - SPHERE
    ////////////////////////////////////////////////////////////////////////////

    // sphere = new cShapeSphere(0.06);
    // world->addChild(sphere);
    // sphere->setLocalPos(0.0, 0.0, 0.35);
    // sphere->createEffectSurface();
    // sphere->m_material->setStiffness(0.8 * maxStiffness);
    // sphere->m_material->setGrayLight();


    // // create a box and define its dimensions
    // box = new cShapeBox(0.7, 0.7, 0.05);
    // // add object to world
    // world->addChild(box);
    // box->setLocalPos(0.0, 0.0, -0.1);
    // // set haptic properties
    // box->m_material->setStiffness(500);
    // // create a haptic surface effect
    // box->createEffectSurface();

    // box1 = new cShapeBox(0.1, 0.1, 0.05);
    // box->addChild(box1);
    // box1->setLocalPos(0.0, 0.0, 0.1);
    // box1->m_material->setStiffness(500);
    // box1->createEffectSurface();
    // box1->m_material->setRedCrimson();
    

    //--------------------------------------------------------------------------
    // WIDGETS
    //--------------------------------------------------------------------------

    // create a font
    font = NEW_CFONTCALIBRI20();

    // create a label to display the haptic and graphic rate of the simulation
    labelRates = new cLabel(font);
    camera->m_frontLayer->addChild(labelRates);

    // set font color
    labelRates->m_fontColor.setBlack();

    // create a background
    background = new cBackground();
    camera->m_backLayer->addChild(background);

    // set background properties
    background->setCornerColors(cColorf(1.0, 1.0, 1.0),
                                cColorf(1.0, 1.0, 1.0),
                                cColorf(0.8, 0.8, 0.8),
                                cColorf(0.8, 0.8, 0.8));

    // a widget panel
    panel = new cPanel();
    camera->m_frontLayer->addChild(panel);
    panel->setSize(100, 135);
    panel->m_material->setGrayDim();
    panel->setTransparencyLevel(0.8);

    labelMousePos = new cLabel(font);
    panel->addChild(labelMousePos);
    labelMousePos->setLocalPos(15, 10, 0.1);
    labelMousePos->m_fontColor.setWhite();

    // create some labels
    labelRed = new cLabel(font);
    panel->addChild(labelRed);
    labelRed->setText("red");
    labelRed->setLocalPos(15, 30, 0.1);
    labelRed->m_fontColor.setWhite();

    labelGreen = new cLabel(font);
    panel->addChild(labelGreen);
    labelGreen->setText("green");
    labelGreen->setLocalPos(15, 50, 0.1);
    labelGreen->m_fontColor.setWhite();

    labelBlue = new cLabel(font);
    panel->addChild(labelBlue);
    labelBlue->setText("blue");
    labelBlue->setLocalPos(15, 70, 0.1);
    labelBlue->m_fontColor.setWhite();

    labelOrange = new cLabel(font);
    panel->addChild(labelOrange);
    labelOrange->setText("orange");
    labelOrange->setLocalPos(15, 90, 0.1);
    labelOrange->m_fontColor.setWhite();

    labelGray = new cLabel(font);
    panel->addChild(labelGray);
    labelGray->setText("gray");
    labelGray->setLocalPos(15, 110, 0.1);
    labelGray->m_fontColor.setWhite();

    // create a label with a small message
    labelMessage = new cLabel(font);
    camera->m_frontLayer->addChild(labelMessage);

    // set font color
    labelMessage->m_fontColor.setBlack();

    // set text message
    labelMessage->setText("use mouse to select and move objects");


//--------------------------------------------------------------------------------------
//testing

    ODEWorld = new cODEWorld(world);
    world->addChild(ODEWorld);
    ODEWorld->setGravity(cVector3d(0.00, 0.00, -9.81));
    cMaterial mat0, mat1, mat2, mat3;


    ODEBody0 = new cODEGenericBody(ODEWorld);
    cMesh* object0 = new cMesh();

    double size = 0.05;
    double radius = 0.15;
    cCreateBox(object0, size, size, size);
    object0->createAABBCollisionDetector(toolRadius);

    
    // mat0.setRedIndian();
    // mat0.setStiffness(0.3 * maxStiffness);
    // mat0.setDynamicFriction(0.6);
    // mat0.setStaticFriction(0.6);
    // object0->setMaterial(mat0);

    // ODEBody0->setImageModel(object0);
    // ODEBody0->createDynamicBox(size, size, size);
    // ODEBody0->setMass(0.05);
    // ODEBody0->setLocalPos(0.0,0,0.2);
    // ODEBody0->rotateAboutGlobalAxisDeg(0,0,1, 45);
//-------------------------
    ODEBody1 = new cODEGenericBody(ODEWorld);
    cMesh* object1 = new cMesh();
    cCreateSphere(object1, radius); //could use radius of 0.1 for a good size for the ball
    object1->createAABBCollisionDetector(toolRadius);

    mat1.setBlueAqua();
    mat1.setStiffness(0.3 * maxStiffness);
    mat1.setDynamicFriction(0.6);
    mat1.setStaticFriction(0.6);
    object1->setMaterial(mat1);

    ODEBody1->setImageModel(object1);
    ODEBody1->createDynamicSphere(radius);
    ODEBody1->setMass(0.05);
    ODEBody1->setLocalPos(0.0,0.0,0.0);
    ODEBody1->rotateAboutGlobalAxisDeg(0,0,1, 45);


// Create a wall
    ODEBody2 = new cODEGenericBody(ODEWorld);
    cMesh* object2 = new cMesh();

    object2->createAABBCollisionDetector(toolRadius);
    cCreateBox(object2,
               0.5, 0.5, 0.5,
               cVector3d(0,0,0),
               cIdentity3d(),
               cColorf(1.0, 1.0, 1.0, 1.0));

    mat2.setGreenDarkCyan();
    mat2.setStiffness(0.3 * maxStiffness);
    mat2.setDynamicFriction(0.6);
    mat2.setStaticFriction(0.6);
    object2->setMaterial(mat2);

    ODEBody2->setImageModel(object2);
    ODEBody2->createDynamicBox(0.5, 0.5, 0.5, true);




//--------------------------
    // double board_size = 0.40;
    // double board_thickness = 0.05;
    // ODEBody2 = new cODEGenericBody(ODEWorld);
    // //ODEBody2->createDynamicBox(board_size, board_size, board_thickness, true);
    // cMesh* object2 = new cMesh();
    // cCreateBox(object2, board_size, board_size, board_thickness);
    // object2->createAABBCollisionDetector(toolRadius);

    // mat2.setGreenDarkCyan();
    // mat2.setStiffness(0.3 * maxStiffness);
    // mat2.setDynamicFriction(0.6);
    // mat2.setStaticFriction(0.6);
    // object2->setMaterial(mat2);

    // ODEBody2->setImageModel(object2);
    // ODEBody2->createDynamicBox(board_size, board_size, board_thickness);
    // //ODEBody2->setMass(0);
    // ODEBody2->setLocalPos(0.5,0.5,-0.5);
//--------------------------------------
    double board_size1 = 0.40;
    double board_thickness1 = 0.05;

    ODEBody3 = new cODEGenericBody(ODEWorld);
    

    cMesh* object3 = new cMesh();
    cCreateBox(object3, 2.5, 2.5, 0.05);
    object3->createAABBCollisionDetector(toolRadius);

    mat3.setPinkHot();
    mat3.setStiffness(0.3 * maxStiffness);
    mat3.setDynamicFriction(0.9);
    mat3.setStaticFriction(0.9);
    object3->setMaterial(mat3);

    ODEBody3->setImageModel(object3);
    ODEBody3->createDynamicBox(2.5, 2.5, 0.05, true);
    ODEBody3->setMass(0.05);
    ODEBody3->setLocalPos(0.0,0.0,-0.5);









//------------------------------------------------
    ODEGPlane0 = new cODEGenericBody(ODEWorld);
    ODEGPlane1 = new cODEGenericBody(ODEWorld);
    ODEGPlane2 = new cODEGenericBody(ODEWorld);
    ODEGPlane3 = new cODEGenericBody(ODEWorld);
    ODEGPlane4 = new cODEGenericBody(ODEWorld);
    ODEGPlane5 = new cODEGenericBody(ODEWorld);

    w = 1.0;
    ODEGPlane0->createStaticPlane(cVector3d(0.0, 0.0,  0.5 * w), cVector3d(0.0, 0.0 ,-1.0));
    ODEGPlane1->createStaticPlane(cVector3d(0.0, 0.0, -w), cVector3d(0.0, 0.0 , 1.0));
    ODEGPlane2->createStaticPlane(cVector3d(0.0,  w, 0.0), cVector3d(0.0,-1.0, 0.0));
    ODEGPlane3->createStaticPlane(cVector3d(0.0, -w, 0.0), cVector3d(0.0, 1.0, 0.0));
    ODEGPlane4->createStaticPlane(cVector3d( w, 0.0, 0.0), cVector3d(-1.0,0.0, 0.0));
    ODEGPlane5->createStaticPlane(cVector3d(-0.8 * w, 0.0, 0.0), cVector3d( 1.0,0.0, 0.0));

    cMesh* ground = new cMesh();
    ODEWorld->addChild(ground);

    double groundSize = 3.0;
    cCreatePlane(ground, groundSize, groundSize);

    ground->setLocalPos(0.0, 0.0, -1.0);

    cMaterial matGround;
    matGround.setStiffness(0.3 * maxStiffness);
    matGround.setDynamicFriction(0.2);
    matGround.setStaticFriction(0);
    matGround.setWhite();
    matGround.m_emission.setGrayLevel(0.3);
    ground->setMaterial(matGround);

    ground->createAABBCollisionDetector(toolRadius);
//----------------------------------------------------------
    
// Roof    
/*
    cMesh* wall1 = new cMesh();
    ODEWorld->addChild(wall1);

    //double groundSize = 3.0;
    cCreatePlane(wall1, 3, 3);

    wall1->setLocalPos(0.0, 0.0, 1.0);

    cMaterial matGround1;
    matGround1.setStiffness(0.3 * maxStiffness);
    matGround1.setDynamicFriction(0.2);
    matGround1.setStaticFriction(0);
    matGround1.setBlueAqua();
    matGround1.m_emission.setGrayLevel(0.3);
    wall1->setMaterial(matGround1);

    wall1->createAABBCollisionDetector(toolRadius);

// Black Left Wall
    cMesh* wall2 = new cMesh();
    ODEWorld->addChild(wall2);

    //double groundSize = 3.0;
    cCreatePlane(wall2, 3, 3);

    wall2->setLocalPos(1.0, 0.0, 0.0);
    wall2->rotateAboutGlobalAxisRad(cVector3d(0.0, -1.0, 0.0),1.57);

    cMaterial matGround2;
    matGround2.setStiffness(0.3 * maxStiffness);
    matGround2.setDynamicFriction(0.2);
    matGround2.setStaticFriction(0);
    matGround2.setBlack();
    matGround2.m_emission.setGrayLevel(0.3);
    wall2->setMaterial(matGround2);
    wall2->createAABBCollisionDetector(toolRadius);


//Black Right Wall
    cMesh* wall3 = new cMesh();
    ODEWorld->addChild(wall3);

    //double groundSize = 3.0;
    cCreatePlane(wall3, 3, 3);

    wall3->setLocalPos(-1.0, 0.0, 0.0);
    wall3->rotateAboutGlobalAxisRad(cVector3d(0.0,-1.0, 0.0),1.57);

    cMaterial matGround3;
    matGround3.setStiffness(0.3 * maxStiffness);
    matGround3.setDynamicFriction(0.2);
    matGround3.setStaticFriction(0);
    matGround3.setBlack();
    matGround3.m_emission.setGrayLevel(0.3);
    wall3->setMaterial(matGround3);

    wall3->createAABBCollisionDetector(toolRadius);


// Black Front Wall
    cMesh* wall4 = new cMesh();
    ODEWorld->addChild(wall4);

    //double groundSize = 3.0;
    cCreatePlane(wall4, 3, 3);

    wall4->setLocalPos(0.0, -1.0, 0.0);
    wall4->rotateAboutGlobalAxisRad(cVector3d(1.0,0.0, 0.0),1.57);

    cMaterial matGround4;
    matGround4.setStiffness(0.3 * maxStiffness);
    matGround4.setDynamicFriction(0.2);
    matGround4.setStaticFriction(0);
    matGround4.setBlack();
    matGround4.m_emission.setGrayLevel(0.3);
    wall4->setMaterial(matGround4);

    wall4->createAABBCollisionDetector(toolRadius);
*/

//---------------------------------------------
// Obstacles

Obstacle* one = new Obstacle();
one->initialise(cVector3d( 0.0, 0.0, 1.0), cVector3d(0.0,0.0, 1.0));










//-------------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    // START SIMULATION
    //--------------------------------------------------------------------------

    // create a thread which starts the main haptics rendering loop
    hapticsThread = new cThread();
    hapticsThread->start(updateHaptics, CTHREAD_PRIORITY_HAPTICS);

    // setup callback when application exits
    atexit(close);


    //--------------------------------------------------------------------------
    // MAIN GRAPHIC LOOP
    //--------------------------------------------------------------------------

    // call window size callback at initialization
    windowSizeCallback(window, width, height);

    // main graphic loop
    while (!glfwWindowShouldClose(window))
    {
        // get width and height of window
        glfwGetWindowSize(window, &width, &height);

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

    // exit
    return 0;
}

//------------------------------------------------------------------------------

void windowSizeCallback(GLFWwindow* a_window, int a_width, int a_height)
{
    // update window size
    width  = a_width;
    height = a_height;

    // update panel position
    panel->setLocalPos(10, (height - panel->getHeight()) - 10);

    // update position of label
    labelMessage->setLocalPos((int)(0.5 * (width - labelMessage->getWidth())), 40);
}

//------------------------------------------------------------------------------

void errorCallback(int a_error, const char* a_description)
{
    cout << "Error: " << a_description << endl;
}

//------------------------------------------------------------------------------

void keyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods)
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

    // option - toggle fullscreen
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

    // option - toggle vertical mirroring
    else if (a_key == GLFW_KEY_M)
    {
        mirroredDisplay = !mirroredDisplay;
        camera->setMirrorVertical(mirroredDisplay);
    }

    else if (a_key == GLFW_KEY_G)
    {
        if (ODEWorld->getGravity().length() > 0.0)
        {
            ODEWorld->setGravity(cVector3d(0.0, 0.0, 0.0));
        }
        else
        {
            ODEWorld->setGravity(cVector3d(0.0, 0.0, -9.81));
        }
    }

    else if (a_key == GLFW_KEY_A)
    {
        cVector3d temp = ODEBody2->getLocalPos();
        temp = temp + cVector3d(0,0,0.5);
        ODEBody2->setLocalPos(temp);
    }

    else if (a_key == GLFW_KEY_S)
    {
        cVector3d temp = ODEBody2->getLocalPos();
        temp = temp + cVector3d(0,0.5,0);
        ODEBody2->setLocalPos(temp);
    }

    //for camera movement, not working as intended, can be fixed later
    else if (a_key == GLFW_KEY_C)
    {   
        angle += 30;
        double newY = 3.5 * cos(angle);
        double newX = 3.5 * sin(angle);
        camera->set(cVector3d(newX, newY, 1.5),    // camera position (eye) cVector3d(0.8, 0.8, 0.6), 
                    cVector3d(0.0, 0.0, 0.0),    // lookat position (target)
                    cVector3d(0.0, 0.0, 1.0));   // direction of the (up) vector
        cout << "angle: " << angle << " camerapos: " << camera->getLocalPos() << "\n";
        //cout << "gren angle: " << ODEBody2->getLocalPos() << "\n";
    }

    else if (a_key == GLFW_KEY_V)
    {   
        angle -= 3;
        double newY = 3.5 * sin(angle);
        double newX = 3.5 * sin(angle);
        cout << "angle: " << angle << " camerapos: " << camera->getLocalPos() << "\n";
        camera->set(cVector3d(newX, newY, 1.5),    // camera position (eye) cVector3d(0.8, 0.8, 0.6), 
                    cVector3d(0.0, 0.0, 0.0),    // lookat position (target)
                    cVector3d(0.0, 0.0, 1.0));   // direction of the (up) vector
    }
}

//------------------------------------------------------------------------------

void mouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods)
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
        if(hit)
        {
            // reset all label font colors to white
            labelMousePos->m_fontColor.setWhite();
            labelRed->m_fontColor.setWhite();
            labelGreen->m_fontColor.setWhite();
            labelBlue->m_fontColor.setWhite();
            labelOrange->m_fontColor.setWhite();
            labelGray->m_fontColor.setWhite();

            // check mouse selection
            if (recorder.m_nearestCollision.m_object == labelRed)
            {
                labelRed->m_fontColor.setBlack();
                if (selectedObject != NULL)
                    selectedObject->m_material->setRedCrimson();
            }
            else if (recorder.m_nearestCollision.m_object == labelGreen)
            {
                labelGreen->m_fontColor.setBlack();
                if (selectedObject != NULL)
                    selectedObject->m_material->setGreenLightSea();
            }
            else if (recorder.m_nearestCollision.m_object == labelBlue)
            {
                labelBlue->m_fontColor.setBlack();
                if (selectedObject != NULL)
                    selectedObject->m_material->setBlueCornflower();
            }
            else if (recorder.m_nearestCollision.m_object == labelOrange)
            {
                labelOrange->m_fontColor.setBlack();
                if (selectedObject != NULL)
                    selectedObject->m_material->setOrangeRed();
            }
            else if (recorder.m_nearestCollision.m_object == labelGray)
            {
                labelGray->m_fontColor.setBlack();
                if (selectedObject != NULL)
                    selectedObject->m_material->setGrayLight();
                
                // Rotate the board
                cVector3d norm(1, 0, 0);
                //box->rotateAboutGlobalAxisRad(norm, 0.5);
            }
        }
        else
        {
            // detect for any collision between mouse and world
            bool hit = camera->selectWorld(mouseX, (height - mouseY), width, height, recorder, settings);
            if (hit)
            {
                sphereSelect->setShowEnabled(true);
                normalSelect->setShowEnabled(true);
                selectedPoint = recorder.m_nearestCollision.m_globalPos;
                sphereSelect->setLocalPos(selectedPoint);
                normalSelect->m_pointA.zero();
                normalSelect->m_pointB = 0.1 * recorder.m_nearestCollision.m_globalNormal;
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

//------------------------------------------------------------------------------

void mouseMotionCallback(GLFWwindow* a_window, double a_posX, double a_posY)
{
    if ((selectedObject != NULL) && (mouseState == MOUSE_SELECTION))
    {
        // get the vector that goes from the camera to the selected point (mouse click)
        cVector3d vCameraObject = selectedPoint - camera->getLocalPos();

        // get the vector that point in the direction of the camera. ("where the camera is looking at")
        cVector3d vCameraLookAt = camera->getLookVector();

        // compute the angle between both vectors
        double angle = cAngle(vCameraObject, vCameraLookAt);

        // compute the distance between the camera and the plane that intersects the object and 
        // which is parallel to the camera plane
        double distanceToObjectPlane = vCameraObject.length() * cos(angle);

        // convert the pixel in mouse space into a relative position in the world
        double factor = (distanceToObjectPlane * tan(0.5 * camera->getFieldViewAngleRad())) / (0.5 * height);
        double posRelX = factor * (a_posX - (0.5 * width));
        double posRelY = factor * ((height - a_posY) - (0.5 * height));

        // compute the new position in world coordinates
        cVector3d pos = camera->getLocalPos() +
            distanceToObjectPlane * camera->getLookVector() +
            posRelX * camera->getRightVector() +
            posRelY * camera->getUpVector();

        // compute position of object by taking in account offset
        cVector3d posObject = pos - selectedObjectOffset;

        // apply new position to object
        //selectedObject->setLocalPos(posObject);

        // place cursor at the position of the mouse click
        sphereSelect->setLocalPos(pos);
        
        prevMouseX = mouseX;
        prevMouseY = mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        
        cVector3d norm1(-(mouseX - prevMouseX), (mouseY - prevMouseY), 0); //x y z
        //box->rotateAboutGlobalAxisRad(norm1, 0.02);

        ODEBody3->rotateAboutGlobalAxisRad(norm1, 0.02);
    }
}

//------------------------------------------------------------------------------

void close(void)
{
    // stop the simulation
    simulationRunning = false;

    // wait for graphics and haptics loops to terminate
    while (!simulationFinished) { cSleepMs(100); }

    // close haptic device
    hapticDevice->close();

    // delete resources
    delete hapticsThread;
    delete world;
    delete handler;
}

//------------------------------------------------------------------------------

void updateGraphics(void)
{
    /////////////////////////////////////////////////////////////////////
    // UPDATE WIDGETS
    /////////////////////////////////////////////////////////////////////

    // update haptic and graphic rate data
    labelRates->setText(cStr(freqCounterGraphics.getFrequency(), 0) + " Hz / " +
                        cStr(freqCounterHaptics.getFrequency(), 0) + " Hz");
    glfwGetCursorPos(window, &mouseX, &mouseY);
    labelMousePos->setText(cStr(mouseX, 0) + ", " + cStr(mouseY, 0));

    // update position of label
    labelRates->setLocalPos((int)(0.5 * (width - labelRates->getWidth())), 15);

    /////////////////////////////////////////////////////////////////////
    // RENDER SCENE
    /////////////////////////////////////////////////////////////////////

    // update shadow maps (if any)
    world->updateShadowMaps(false, mirroredDisplay);

    // render world
    camera->renderView(width, height);

    // wait until all GL commands are completed
    glFinish();

    // check for any OpenGL errors
    GLenum err;
    err = glGetError();
    if (err != GL_NO_ERROR) cout << "Error:  %s\n" << gluErrorString(err);




    //test possible goal state logic
    // cVector3d temp = ODEBody1->getLocalPos();
    // temp = temp + cVector3d(0, 0, -0.2);
    // cVector3d temp1 = ODEBody1->getLocalPos();
    // double t = temp->x();
    // if (temp->x() == 3) 
    // {   
    //     cout << "closeclosecloseclosecloseclosecloseclosecloseclose\n";
    //     close();
    // }
}

//------------------------------------------------------------------------------

void updateHaptics(void)
{
    // angular velocity
    cVector3d angVel(0,0,0.1);
    cVector3d linVel(0,0.0,0);

    // reset clock
    cPrecisionClock clock;
    clock.reset();

    // simulation in now running
    simulationRunning  = true;
    simulationFinished = false;

    // reset tool
    tool->initialize();


    // main haptic simulation loop
    while(simulationRunning)
    {
        ////////////////////////////////////////////////////////////////////
        // SIMULATION TIME
        /////////////////////////////////////////////////////////////////////

        // stop the simulation clock
        clock.stop();

        // read the time increment in seconds
        double timeInterval = clock.getCurrentTimeSeconds();

        // restart the simulation clock
        clock.reset();
        clock.start();

        /////////////////////////////////////////////////////////////////////////
        // HAPTIC RENDERING
        /////////////////////////////////////////////////////////////////////////

        // signal frequency counter
        freqCounterHaptics.signal(1);

        // compute global reference frames for each object
        world->computeGlobalPositions(true);

        // update position and orientation of tool
        tool->updateFromDevice();

        // compute interaction forces
        tool->computeInteractionForces();

        // send forces to haptic device
        tool->applyToDevice();

        /////////////////////////////////////////////////////////////////////
        // DYNAMIC SIMULATION
        /////////////////////////////////////////////////////////////////////

        // get position of cursor in global coordinates
        cVector3d toolPos = tool->getDeviceGlobalPos();

        // get position of object in global coordinates
        //cVector3d objectPos = sphere->getGlobalPos();
        //cVector3d boxPos = box->getGlobalPos();

        // compute a vector from the center of mass of the object (point of rotation) to the tool
        //cVector3d v = cSub(toolPos, objectPos);

        // compute angular acceleration based on the interaction forces
        // between the tool and the object
        cVector3d angAcc(0,0,0);
        cVector3d linAcc(0,0,0);
        cVector3d forceTool(0,0,0);

        // compute force that centers object at origin
        //cVector3d force = -0.2 * objectPos;

        // update linear acceleration
        // const double MASS = 1.0;
        // linAcc = (1.0 / MASS) * (force + forceTool);

        // update angular velocity
        // angVel.add(timeInterval * angAcc);

        // // update linear velocity
        // linVel.add(timeInterval * linAcc);

        // TODO
        // simulate collision
        // if (objectPos.z() < boxPos.z() + 0.1)
        // {
        //     linVel.z(-linVel.z());
        // }

        // set a threshold on the rotational velocity term
        // const double MAX_ANG_VEL = 10.0;
        // double vel = angVel.length();
        // if (vel > MAX_ANG_VEL)
        // {
        //     angVel.mul(MAX_ANG_VEL / vel);
        // }

        // add some damping too
        // const double DAMPING = 0.1;
        // angVel.mul(1.0 - DAMPING * timeInterval);
        // linVel.mul(1.0 - DAMPING * timeInterval);

        // if user switch is pressed, set velocity to zero
        // if (tool->getUserSwitch(0) == 1)
        // {
        //     angVel.zero();
        //     linVel.zero();
        // }

        // // compute the next rotation configuration of the object
        // if (angVel.length() > C_SMALL)
        // {
        //     sphere->rotateAboutGlobalAxisRad(cNormalize(angVel), timeInterval * angVel.length());
        // }

        // compute the next position of the object
        // cVector3d nextPos = sphere->getLocalPos() + (timeInterval * linVel);
        // sphere->setLocalPos(nextPos);


        ODEWorld->updateDynamics(timeInterval);
    }

    // exit haptics thread
    simulationFinished = true;
}

//------------------------------------------------------------------------------

