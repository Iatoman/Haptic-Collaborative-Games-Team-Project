#include "Haptic.h"
#include "World.h"
#include "Mouse.h"
#include "Map.h"
#include "Game.h"

using namespace chai3d;

//---------------------------------------------
// DECLARED VARIABLES (HAPTICS)
//---------------------------------------------

// a haptic device handler
cHapticDeviceHandler* handler;

// a pointer to the current haptic device
cGenericHapticDevicePtr hapticDevice;

// a global variable to store the position [m] of the haptic device
cVector3d hapticDevicePosition;

// a global variable to store the velocity of the device
cVector3d hapticDeviceVelocity;

// information about the current haptic device (TODO: no global var)
cHapticDeviceInfo hapticDeviceInfo;

// a flag to indicate if the haptic simulation currently running
bool simulationRunning;

// a flag to indicate if the haptic simulation has terminated
bool simulationFinished;


//---------------------------------------------
// DECLARED VARIABLES (TOOLS)
//---------------------------------------------

// a virtual tool representing the haptic device in the scene
cGenericTool* tool;

// a frequency counter to measure the simulation haptic rate
cFrequencyCounter freqCounterHaptics;


//---------------------------------------------
// DECLARED FUNCTIONS
//---------------------------------------------

/**
 * @brief An example to retrieve info from the haptic device.
 * 
 * @note This function is just a demonstration of the information which can 
 *     be obtained from the haptic device. Since all variables are local,
 *     this function will not have real effects. To obtain certain information,
 *     just invoke the corresponding method in `hapticDevice` global variable.
 * 
 * @warning All method parameters are passed by **reference**.
 */
void getHapticInfo()
{
    // read position 
    cVector3d position;
    hapticDevice->getPosition(position);
    
    // read orientation 
    cMatrix3d rotation;
    hapticDevice->getRotation(rotation);

    // read gripper position
    double gripperAngle;
    hapticDevice->getGripperAngleRad(gripperAngle);

    // read linear velocity 
    cVector3d linearVelocity;
    hapticDevice->getLinearVelocity(linearVelocity);

    // read angular velocity
    cVector3d angularVelocity;
    hapticDevice->getAngularVelocity(angularVelocity);

    // read gripper angular velocity
    double gripperAngularVelocity;
    hapticDevice->getGripperAngularVelocity(gripperAngularVelocity);
}

/**
 * @brief Initializes haptic device / tools and retrieve info about the current haptic device 
 * 
 * @warning This function should be called in World or Game, because `updateHaptics`
 *     is an infinite loop.
 */
void initHapticDevice(cBulletWorld *bulletWorld)
{
    // create a haptic device handler
    handler = new cHapticDeviceHandler();

    // get a handle to the first haptic device
    handler->getDevice(hapticDevice, 0);

    // retrieve information about the current haptic device
    hapticDeviceInfo = hapticDevice->getSpecifications();

    // create a tool (gripper or pointer)
    if (hapticDeviceInfo.m_actuatedGripper)
        tool = new cToolGripper(bulletWorld);
    else
        tool = new cToolCursor(bulletWorld);
        
    // insert tool into world
    bulletWorld->addChild(tool);

    // // open a connection to haptic device
    // hapticDevice->open();

    // // calibrate device (if necessary)
    // hapticDevice->calibrate();
    
    /* NOTE: in this implementation, the tool is a sphere object in the world */

    // connect the haptic device to the virtual tool
    tool->setHapticDevice(hapticDevice);

    // map the physical workspace of the haptic device to a larger virtual workspace.
    // tool->setWorkspaceRadius(1.3);

    // define a radius for the virtual tool contact points (sphere)
    double toolRadius = 0.06;
    tool->setRadius(toolRadius, toolRadius);

    // if the device has a gripper, enable the gripper to simulate a user switch
    // hapticDevice->setEnableGripperUserSwitch(true);

    // enable if objects in the scene are going to rotate of translate
    // or possibly collide against the tool. If the environment
    // is entirely static, you can set this parameter to "false"
    tool->enableDynamicObjects(true);

    // haptic forces are enabled only if small forces are first sent to the device;
    // this mode avoids the force spike that occurs when the application starts when 
    // the tool is located inside an object for instance. 
    tool->setWaitForSmallForce(true);

    // start the haptic tool
    tool->start();
}

/**
 * @brief Creates a force field (like a spring) and apply the force to the haptic device.
 * 
 * @note According to Hooke's law (F = -kx), by computing the difference between the desired position 
 *     and current position, we can calculate the force applied to the device.
 * 
 * - After calculation, new force will be applied to the `force` parameter directly.
 * - This is a simplified version compared to the original one, which also computes angular torque.
 * - It is also possible to create multiple force fields simultaneously, and the
 *   overall effect is the net force of those fields.
 * 
 * @param force         original force to be modified (pass by reference)
 * @param desiredPos    desired position
 * @param position      current position
 * @param Kp            stiffness of the spring [N/m] (suggested range: 10-100 N/m)
 */
void addForceField(cVector3d& force, cVector3d desiredPos, cVector3d position, double Kp)
{
    cVector3d forceField = Kp * (desiredPos - position);
    force.add(forceField);
}

/**
 * @brief Add damping term to the device.
 * 
 * @note A simplified version ignoring angular and gripper angular damping force.
 * 
 * @param force             original force to be modified
 * @param linearVelocity    linear velocity of the haptic device
 */
void addDamping(cVector3d& force, cVector3d linearVelocity)
{
    hapticDeviceInfo = hapticDevice->getSpecifications();

    // compute linear damping force
    double Kv = 1.0 * hapticDeviceInfo.m_maxLinearDamping;
    cVector3d forceDamping = -Kv * linearVelocity;
    force.add(forceDamping);
}

/**
 * @brief Add AABB collision detector to a given object.
 * 
 * @param obj           a bullet mesh object to be modified 
 * @param toolRadius    radius of the haptic tool
 */
void addCollisionDetector(cBulletMesh *obj, double toolRadius)
{
    obj->createAABBCollisionDetector(toolRadius);
}

/**
 * @brief This function deals with the mouse version of the game.
 * 
 */
void updateMouse(void)
{
    simulationRunning  = true;                      // simulation in now running
    simulationFinished = false;                     // simulation in now running
    cPrecisionClock clock;                          // reset clock
    clock.reset();                                  // reset clock
    tool->setDeviceLocalPos(1,1,-1);

    Map map(ROW, COL);

    while(simulationRunning)
    {
        clock.stop();                               // stop the simulation clock
        double timeInterval = cClamp(clock.getCurrentTimeSeconds(), 0.0001, 0.001); // read the time increment in seconds
        clock.reset();                              // restart the simulation clock
        clock.start();                              // restart the simulation clock
        freqCounterHaptics.signal(1);               // signal frequency counter

        world->computeGlobalPositions(true);        // compute global reference frames for each object

        // obtain the ball position
        cVector3d ballPos = ball->getGlobalPos();

        // apply force to ball
        cVector3d force1 = selectedPoint;
        force1.sub(ballPos);
        force1.mul(2.0);

        // apply A* to find the next point of the shortest path
        cVector3d nextPoint = map.findNextPos(ballPos);

        // apply force to the next point
        cVector3d force2 = nextPoint;
        force2.sub(ballPos);
        force2.normalize();
        force2.mul(1.2);

        cVector3d force(0, 0, 0);
        if (useForceField)
            force.add(force1);
        if (useDamping)
            force.add(force2);
        ball->addExternalForce(force);

        // check whether the ball falls down
        if (isBallFallen())
            resetBall();

        world->updateDynamics(timeInterval);  // update simulation
    }
    simulationFinished = true;
}

/**
* @brief This function deals with the haptic version of the game.
* 
*/
void updateHaptics(void)
{
    // simulation is now running
    simulationRunning = true;
    simulationFinished = false;

    // reset clock
    cPrecisionClock clock;
    clock.reset();

    // initialize map
    Map map(ROW, COL);

    // main haptic simulation loop
    while (simulationRunning)
    {

        /////////////////////////////////////////////////////////////////////
        // SIMULATION TIME 
        /////////////////////////////////////////////////////////////////////

        // stop the simulation clock
        clock.stop();

        // read the time increment in seconds
        double timeInterval = cClamp(clock.getCurrentTimeSeconds(), 0.0001, 0.001);

        // restart the simulation clock
        clock.reset();
        clock.start();

        // signal frequency counter
        freqCounterHaptics.signal(1);


        /////////////////////////////////////////////////////////////////////
        // HAPTIC FORCE COMPUTATION
        /////////////////////////////////////////////////////////////////////

        // compute global reference frames for each object
        world->computeGlobalPositions(true);

        // update position and orientation of tool
        tool->updateFromDevice();

        // compute interaction forces
        tool->computeInteractionForces();

        // read haptic position
        hapticDevice->getPosition(hapticDevicePosition);

        // read haptic velocity
        hapticDevice->getLinearVelocity(hapticDeviceVelocity);

        // read ball position
        cVector3d ballPos = ball->getGlobalPos();

        // apply force to ball
        cVector3d force (0, 0, 0);
        force.add(hapticDevicePosition);
        force.sub(ballPos);
        force.z(0);
        force.normalize();

        ball->addExternalForce(force);

        // apply A* to find the next position on the shortest path
        cVector3d nextPoint = map.findNextPos(hapticDevicePosition);

        /**
        * @brief role exchange machanism
        * 
        * @note Adjust the force applied to the haptic device according to the current
        * velocity of the haptic device. The faster the user moves the device, the
        * less AI force will be.
        */
        cVector3d hapticVelocity (0, 0, 0);
        hapticDevice->getAngularVelocity(hapticVelocity);
        double k = 1.0 / (0.1 * hapticVelocity.length() + 0.02);

        // calculate force exerted on haptic device
        cVector3d hapticForce (0, 0, 0);
        addForceField(hapticForce, nextPoint, hapticDevicePosition, k);
        hapticForce.z(0);
        hapticDevice->setForce(hapticForce);

        // check whether the ball falls down
        if (isBallFallen())
            resetBall();

        // update simulation
        world->updateDynamics(timeInterval);
    }
}
