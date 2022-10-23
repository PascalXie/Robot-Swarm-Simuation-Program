#ifndef DECISIONMAKING_H
#define DECISIONMAKING_H

#include <iostream>
#include <string>
#include <vector>

#include "AbstractRobotUnit.h"
#include "AbstractTargetUnit.h"
#include "AbstractTaskUnit.h"

#include "Algorithm.h"

using namespace std;

class DecisionMaking
{
	public:
        DecisionMaking();
        ~DecisionMaking();

	public:
		// decistion making name 
		string decisionMakingName;

        // the task unit
        AbstractTaskUnit* taskUnit;

        // the map
        std::vector<std::vector<int>> map;

    // flags
	public:
        bool isTaskUnitSet;
        bool isMapSet;

	public:
		// show all parameters
		virtual void showAllParameters() = 0;

    // Do Decision making
    public:
        // part 1 : task allocation
		virtual int doTaskAllocation() = 0;

        // part 2 : path planning for all robots
		virtual int doPathPlanning() = 0;

    // set the task unit
	public:
		void setATaskUnit(AbstractTaskUnit* taskUnit_);

    // set the map
	public:
		void setTheMap(std::vector<std::vector<int>> map_);

};

#endif // DECISIONMAKING_H

