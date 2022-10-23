#ifndef BASICDECISIONMAKING_H
#define BASICDECISIONMAKING_H

#include <iostream>
#include <string>
#include <vector>

#include "DecisionMaking.h"

#include "CNCUnit.h"
#include "AGVUnit.h"
#include "LoadingTaskUnit.h"

#include "Algorithm.h"


using namespace std;

class BasicDecisionMaking : virtual public DecisionMaking
{
	public:
		BasicDecisionMaking(string decisionMakingName_);
		~BasicDecisionMaking();

	public:
		// show all parameters
		void showAllParameters();

    // Do Decision making
    public:
        // part 1 : task allocation
		int doTaskAllocation();

        // part 2 : path planning for all robots
		int doPathPlanning();

    //tools for map
    public:
        void showTheMap(std::vector<std::vector<int>> map_);

    // flags 
    public:
        bool dosePathPlanningConsiderRobotAsObstacle;

};

#endif // BASICDECISIONMAKING_H
