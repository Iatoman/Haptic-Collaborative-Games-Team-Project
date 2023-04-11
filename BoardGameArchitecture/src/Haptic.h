/**
 * @file Haptic.h
 * @author your name (you@domain.com)
 * @version 0.1
 * @date 2022-04-24
 * 
 * @brief This header file contains all components related to haptic feedback and haptic device.
 * 
 * @note The global variable `hapticDevice` is a vital component in manipulating the haptic device.
 *      including: position, rotation, force, torque, specification, velocity...
 * 
 * @copyright Copyright (c) 2022
 * 
 * @todo `hapticsThread` global variable should be implemented in game / world?
 */
#ifndef HAPTIC_H
#define HAPTIC_H

#include "chai3d.h"
#include "CBullet.h"


//---------------------------------------------
// DECLARED VARIABLES (HAPTICS)
//---------------------------------------------

// a haptic device handler
extern chai3d::cHapticDeviceHandler* handler;

// a pointer to the current haptic device
extern chai3d::cGenericHapticDevicePtr hapticDevice;

// a global variable to store the position [m] of the haptic device
extern chai3d::cVector3d hapticDevicePosition;

// information about the current haptic device
extern chai3d::cHapticDeviceInfo hapticDeviceInfo;

// a flag to indicate if the haptic simulation currently running
extern bool simulationRunning;

// a flag to indicate if the haptic simulation has terminated
extern bool simulationFinished;

//---------------------------------------------
// DECLARED VARIABLES (TOOLS)
//---------------------------------------------

// a virtual tool representing the haptic device in the scene
extern chai3d::cGenericTool* tool;

// a frequency counter to measure the simulation haptic rate
extern chai3d::cFrequencyCounter freqCounterHaptics;



//---------------------------------------------
// DECLARED FUNCTIONS
//---------------------------------------------

// retrieve info from the haptic device
void getHapticInfo(void);

// initialise haptic device / tools and retrieve info about the current haptic device
void initHapticDevice(chai3d::cBulletWorld *world);

// creates a force field (like a spring) and apply the force to the haptic device
void addForceField(chai3d::cVector3d& force, chai3d::cVector3d desiredPos, chai3d::cVector3d position, double Kp);

// adds damping term to the device
void addDamping(chai3d::cVector3d& force, chai3d::cVector3d linearVelocity);

// adds AABB collision detector to a given object
void addCollisionDetector(chai3d::cBulletMesh *obj, double toolRadius);

// mouse version of the game
void updateMouse(void);

// haptic version of the game
void updateHaptics(void);


#endif // HAPTIC_H
