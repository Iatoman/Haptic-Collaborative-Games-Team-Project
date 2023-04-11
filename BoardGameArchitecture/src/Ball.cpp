#include "Ball.h"

/**
 * @brief A function to create a ball
 *     
 * 
 * @param world pointer of the world
 * @param radius radius of the ball
 *
 * @return ball a new created ball
 */
cBulletSphere* createBall(cBulletWorld* world, double radius) {
	cBulletSphere *ball = new cBulletSphere(world, radius);
	ball->setLocalPos(0, 0, 1);
	world->addChild(ball);
	setBallMaterial(ball);
    setBallMass(ball, 0.2);
    setBallCollision(ball, 0.06);
    ball->setSurfaceFriction(0.1);
    ball->buildDynamicModel();
	return ball;
}

/**
 * @brief A function to set material of the ball
 *     
 * 
 * @param ball a ball object
 */
void setBallMaterial(cBulletSphere* ball) {
	cMaterial mat;
	// Set color of material yellow as default 
	mat.setYellowGold();
	mat.setStiffness(0.3 * 1);
	mat.setDynamicFriction(0.6);
    mat.setStaticFriction(0.6);
	// Add material to the ball
	ball->setMaterial(mat);
}

/**
 * @brief A function to set collision of the ball
 *     
 * 
 * @param ball a ball object
 * @param toolRadius radius of the tool
 */
void setBallCollision(cBulletSphere* ball, double toolRadius) {
	ball->createAABBCollisionDetector(toolRadius);
}

/**
 * @brief A function to set location of the ball
 *     
 * 
 * @param x x-coordinate of the ball
 * @param y y-coordinate of the ball
 * @param z z-coordinate of the ball
 */
void setBallSpawnPoint(cBulletSphere* ball, double x, double y, double z) {
	ball->setLocalPos(x, y, z);
}

/**
 * @brief A function to set mass of the ball
 *     
 * 
 * @param ball a ball object
 * @param mass mass of the ball
 */
void setBallMass(cBulletSphere* ball, double mass){
	ball->setMass(mass);
}

/**
 * @brief A function to change color of the ball
 *     
 * 
 * @param ball a ball object
 * @param mat a material object
 */
void changeBallColour(cBulletSphere* ball, cMaterial mat) {
	mat.setBlueAquamarine();
	ball->setMaterial(mat);
}
