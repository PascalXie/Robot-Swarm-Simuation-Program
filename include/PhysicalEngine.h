#ifndef PHYSICALENGINE_H
#define PHYSICALENGINE_H

#include <iostream>
#include <string>

#include "AbstractTaskUnit.h"
#include "AbstractRobotUnit.h"

#include "DecisionMaking.h"

#include "Algorithm.h"

using namespace std;

class PhysicalEngine
{
	public:
		PhysicalEngine(double timeStart_, double timeEnd_, double timeWidth_);
		~PhysicalEngine();

    
    // Start the physical simulation
	public:
        int startSimulation();

    // decision making
    public:
        // set the task
        virtual void setATaskUnit(AbstractTaskUnit* taskUnit_) = 0;

        // set the map
        virtual void setTheMap(std::vector<std::vector<int>> map_) = 0;

        // step 1 : get the task, do decision making
        virtual int doDecisionMaking() = 0;

        // get the task from outside. 
        // robots would be flluctuated in this function
        virtual int fluctuateTaskUnit() = 0;

    // verbose Level
    public:
        void setVerboseLevel(int verboseLevel_);

    // task unit
    public:
        bool isTaskUnitSet;

    // Physical Processing
    public:
        // Do Physical Processing
        virtual int doPhysicalProcessing(AbstractRobotUnit* robot_);

    // data aquisition and restore
    public: 
        // data processing 
        virtual void DataProcessingBeforeEvent() = 0;
        virtual void DataProcessingInEvent() = 0;
        virtual void DataProcessingAfterEvent() = 0;

	// PhysicalEngine's variables are written here
	public:
		double timeStart;
		double timeEnd;
		double timeWidth;
		int timeSize; // number of the time intervals 

    // verbose level for debug
	public:
        int verboseLevel;


    // Decision making
    public:
        DecisionMaking* DM;

    // data
    public:
        int timeLoopID;

};

#endif // PHYSICALENGINE_H

