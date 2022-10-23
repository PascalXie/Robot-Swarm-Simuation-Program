#ifndef ABSTRACTROBOTUNIT_H
#define ABSTRACTROBOTUNIT_H

#include <iostream>
#include <string>

#include "Algorithm.h"

using namespace std;

class AbstractRobotUnit
{
    public: 
        AbstractRobotUnit();
        ~AbstractRobotUnit();

    // Robot variables written here
    public:
        // robot name
        string robotName;

        // robot ID
        int robotID;

        // location
        double currentLocationX;
        double currentLocationY;
        double currentLocationZ;

        // orientation or Pose
        // Part 1 : euler angle, use euler angle for robots in 2D space, in which, Rx
        // = 0, Ry = 0
        double currentOrientationRx;
        double currentOrientationRy;
        double currentOrientationRz;

        // velocity
        double currentVx;
        double currentVy;
        double currentVz;

        // acceleration
        double currentAx;
        double currentAy;
        double currentAz;

        // battery level
        double currentBatteryLevel;

        // robot size
        double currentSizeLength;
        double currentSizeWidth;
        double currentSizeHeight;

        // path writen here, A* from the Algorithm would be used to generate the path
        std::list<std::shared_ptr<Node>> path;

    public:
        // a test function
        virtual void test() = 0;

    public:
        // show all parameters
        virtual void showAllParameters() = 0;

    // A*
    public:
        // set the path
        //void setPath(std::list<Node *> path_);
        void setPath(std::list<std::shared_ptr<Node>> path_);
};

#endif // ABSTRACTROBOTUNIT_H
