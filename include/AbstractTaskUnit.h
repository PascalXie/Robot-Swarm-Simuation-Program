#ifndef ABSTRACTTASKUNIT_H
#define ABSTRACTTASKUNIT_H

#include <iostream>
#include <string>
#include <vector>

#include "AbstractRobotUnit.h"
#include "AbstractTargetUnit.h"
#include "Algorithm.h"

using namespace std;

class AbstractTaskUnit
{
    // Task variables written here
	public:
		// task name 
		string taskName;

		// task ID 
		int taskID;

		// Robot list
		vector<int> robotIDList;
		vector<AbstractRobotUnit*> robotList;

		// Target list
		vector<int> targetIDList;
		vector<AbstractTargetUnit*> targetList;

		// the Robot Target pair, which represents a target and a robot serving it.
        vector<int> robotTargetPairList;


	public:
		// show all parameters
		virtual void showAllParameters() = 0;

	public:
		// add the index of robots and targets
		virtual int addARobotID(int) = 0;
		virtual int addATargetID(int) = 0;

		// add robots and targets
		virtual int addARobot(AbstractRobotUnit*) = 0;
		virtual int addATarget(AbstractTargetUnit*) = 0;

        // set the robot-target pairs
        virtual int setRobotTargetPairList() = 0;

};

#endif // ABSTRACTTASKUNIT_H
