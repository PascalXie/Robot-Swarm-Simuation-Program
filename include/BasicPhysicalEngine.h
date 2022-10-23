#ifndef BASICPHYSICALENGINE_H
#define BASICPHYSICALENGINE_H

#include <fstream>

#include "PhysicalEngine.h"

#include "AGVUnit.h"
#include "Algorithm.h"
#include "LoadingTaskUnit.h"

#include "BasicDecisionMaking.h"


using namespace std;

class BasicPhysicalEngine: virtual public PhysicalEngine
{
	public:
		BasicPhysicalEngine(double timeStart_, double timeEnd_, double timeWidth_);
		~BasicPhysicalEngine();

    // decision making
    public:
        // set the task
        void setATaskUnit(AbstractTaskUnit* taskUnit_);

        // set the map
        void setTheMap(std::vector<std::vector<int>> map_);

        // step 1 : get the task, do decision making
        int doDecisionMaking();

        // get the task from outside
        int fluctuateTaskUnit();

    // Physical Processing
    public:
        // Do Physical Processing
        int doPhysicalProcessing(AbstractRobotUnit* robot_);
    
    // data aquisition and restore
    public: 
        // data processing 
        void DataProcessingBeforeEvent();
        void DataProcessingInEvent();
        void DataProcessingAfterEvent();

    //data processing, file
    private:
        ofstream writeFile;


};

#endif // BASICPHYSICALENGINE_H


