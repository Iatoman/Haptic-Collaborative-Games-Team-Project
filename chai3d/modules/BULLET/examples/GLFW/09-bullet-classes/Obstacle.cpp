#include "Obstacle.h"

Obstacle::Obstacle( cBulletWorld* environment, cBulletBox* container, 
                    double sizeX, double sizeY, double sizeZ, 
                    double posX, double posY, double posZ)
                    //: cBulletBox(environment, sizeX, sizeY, sizeZ)
{
    obstacle = new cBulletBox(environment, sizeX, sizeY, sizeZ);
    container->addChild(obstacle);

    mat.setRed();
    mat.setStiffness(0.3);
    mat.setDynamicFriction(0.9);
    mat.setStaticFriction(0.9);

    obstacle->setMaterial(mat);
    obstacle->buildDynamicModel();
    obstacle->createAABBCollisionDetector(0.06); //toolradius var
    obstacle->setLocalPos(posX, posY, posZ);

} 


/*bulletObstacleTestBorder1 = new cBulletBox(bulletWorld, boardSize, 0.1, 0.5);
    bulletBoard->addChild(bulletObstacleTestBorder1);
    material.setYellowGold();
    bulletObstacleTestBorder1->setMaterial(material);
    bulletObstacleTestBorder1->buildDynamicModel();
    bulletObstacleTestBorder1->createAABBCollisionDetector(toolRadius);
    bulletObstacleTestBorder1->setLocalPos(0.0, -boardSize / 2, 0.0);


material.setRedFireBrick();
    material.setStiffness(0.3 * maxStiffness);
    material.setDynamicFriction(0.9);
    material.setStaticFriction(0.9);*/