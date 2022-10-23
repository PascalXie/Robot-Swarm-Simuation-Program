#ifndef LOADINGTASKUNIT_H
#define LOADINGTASKUNIT_H

#include <iostream>
#include <string>
#include <vector>

#include "AbstractTaskUnit.h"
#include "AGVUnit.h"


using namespace std;

class LoadingTaskUnit : virtual public AbstractTaskUnit
{
    public:
        LoadingTaskUnit();
        ~LoadingTaskUnit();

    public:
        // show all parameters
        void showAllParameters();

    public:
		// add the index of robots and targets
		int addARobotID(int);
		int addATargetID(int);

        // add robots and targets
		int addARobot(AbstractRobotUnit*);
		int addATarget(AbstractTargetUnit*);

        // set the robot-target pairs
        int setRobotTargetPairList();


};

#endif // LOADINGTASKUNIT_H

