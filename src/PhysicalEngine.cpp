#include "PhysicalEngine.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PhysicalEngine::PhysicalEngine(double timeStart_, double timeEnd_, double timeWidth_)
{
    //
	// initialization
    //
	timeStart = timeStart_;
	timeEnd   = timeEnd_;
	timeWidth = timeWidth_;
	timeSize = int((timeEnd-timeStart)/timeWidth);

    // task unit
    isTaskUnitSet = false;

    verboseLevel = 1;

	// checking
	if(timeSize<=0)
	{
		cout<<""<<endl;
		cout<<"!!!!!!!!! Wrong happend in PhysicalEngine::PhysicalEngine: "<<endl;
		cout<<"timeSize is zero or negative : "<<timeSize<<endl;
		cout<<"!!!!!!!!!\n"<<endl;
	}

    cout<<""<<endl;
    cout<<"----"<<endl;
    cout<<"--------------------"<<endl;
    cout<<"This is class PhysicalEngine"<<endl;
    cout<<"timeStart: "<<timeStart<<endl;
    cout<<"timeEnd: "<<timeEnd<<endl;
    cout<<"timeWidth: "<<timeWidth<<endl;
    cout<<"timeSize: "<<timeSize<<endl;
    cout<<""<<endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PhysicalEngine::~PhysicalEngine()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int PhysicalEngine::startSimulation()
{
    cout<<""<<endl;
    cout<<"----"<<endl;
    cout<<"--------------------"<<endl;
    cout<<"PhysicalEngine, simulaiton start..."<<endl;

    // part 0 : data processing, before the loop begin
    cout<<""<<endl;
    cout<<"--------------------"<<endl;
    cout<<"part 0 : data processing, before the loop begin"<<endl;
    // data processing
    DataProcessingBeforeEvent();



    // part 0 : check the task unit
    if(!isTaskUnitSet)
    {
		cout<<""<<endl;
		cout<<"!!!!!!!!! Wrong happend in PhysicalEngine::startSimulation: "<<endl;
		cout<<"The task unit has not been set!"<<endl;
		cout<<"!!!!!!!!!\n"<<endl;

        return 0;
    }

    //
    // part 1 : create a loop, in which every time interval would be processed  
    //
    // step 1 : check timeSize
	if(timeSize<=0)
	{
		cout<<""<<endl;
		cout<<"!!!!!!!!! Wrong happend in PhysicalEngine::startSimulation: "<<endl;
		cout<<"timeSize is zero or negative : "<<timeSize<<endl;
		cout<<"!!!!!!!!!\n"<<endl;

        return 0;
	}

    // step 2 : create the loop, and start the loop
    for(int i=0;i<timeSize;i++)
    {
        // set variables
        timeLoopID = i;

        // bebug
        if(verboseLevel>=1)
        {
            cout<<""<<endl;
            cout<<"----"<<endl;
            cout<<"--------------------"<<endl;
            cout<<"Time Loop ID: "<<i<<endl;
        }
        // !bebug

        //
        // part 2 : do simulation in the time interval
        //
        // step 1 : get the task, do decision making
        int isDecisionMakingGood = doDecisionMaking();

        // step 2 : fluctuate the task unit
        int isTheFluacutationGood = fluctuateTaskUnit();
        if(!isTheFluacutationGood)
        {
            cout<<"The task is NOT GOOD! Check PhysicalEngine::startSimulation and PhysicalEngine::fluctuateTaskUnit!"<<endl;
            return 0;
        }

        // step 2 : create a loop for every robot in the task unit
        for(int j=0;j<DM->taskUnit->robotList.size();j++)
        {

            // bebug
            if(verboseLevel>=1)
            {
                cout<<""<<endl;
                cout<<"----"<<endl;
                cout<<"robot index: "<<j<<endl;
                cout<<"robot name: "<<DM->taskUnit->robotList[j]->robotName<<endl;
            }
            // !bebug

            // step 3 : Start Phyisical Processing
            cout<<"###### step 3 : Start Phyisical Processing"<<endl;
            int isPhysicalProcessingGood = doPhysicalProcessing(DM->taskUnit->robotList[j]);
            cout<<"###### step 3 : Start Phyisical Processing end"<<endl;

            // step 4 : get information from current robot
            // bebug
            if(verboseLevel>=2)
            {
                cout<<""<<endl;
                cout<<"---- Info after the physical processing"<<endl;
                cout<<"index: "<<j<<endl;
                cout<<"robot name: "<<DM->taskUnit->robotList[j]->robotName<<endl;
                cout<<"robot location: ";
                cout<<DM->taskUnit->robotList[j]->currentLocationX<<"; ";
                cout<<DM->taskUnit->robotList[j]->currentLocationY<<"; ";
                cout<<DM->taskUnit->robotList[j]->currentLocationZ<<endl;
                //std::vector<std::vector<int>> map = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                //                                     {1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
                //                                     {1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1},
                //                                     {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1},
                //                                     {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1},
                //                                     {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
                //                                     {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                //                                     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

                vector<vector<int>> map = DM->map;
                  for (size_t row = 0; row < map.size(); ++row) {
                    for (size_t col = 0; col < map[0].size(); ++col) {
                      if (row == DM->taskUnit->robotList[j]->currentLocationX &&
                              col == DM->taskUnit->robotList[j]->currentLocationY){
                          cout << "* ";
                      } else {
                          cout << map[row][col] << " ";
                      }
                    }
                    cout << "\n";
                  }
            }
            // !bebug

        }

        // setp 5 : data processing
        DataProcessingInEvent();

    }

    // part 0 : data processing, before the loop begin
    cout<<""<<endl;
    cout<<"--------------------"<<endl;
    cout<<"part 0 : data processing, before the loop begin"<<endl;
    // data processing
    DataProcessingAfterEvent();

    return 1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// task unit
void PhysicalEngine::setATaskUnit(AbstractTaskUnit* taskUnit_)
{
    //taskUnit = taskUnit_;

    //isTaskUnitSet = true;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// step 1 : get the task, do decision making
int PhysicalEngine::doDecisionMaking()
{
    return 1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// get the task from outside
int PhysicalEngine::fluctuateTaskUnit()
{
    // In this function, the task would be changed according to the needs from outside.
    // Such as fluctuations to the robots. For instance, the slightly change in the location of the robot.

    // In this example, nothing would be fluctuated.

    return 1;
}

////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//// set the path
//void PhysicalEngine::setPath(std::list<Node *> path_)
//{
//    path = path_;
//}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Physical Processing
// Do Physical Processing
int PhysicalEngine::doPhysicalProcessing(AbstractRobotUnit* robot_)
{
    
    // In this function, the robot would be processed.

    // debug
    cout<<".... Pay attention : this is PhysicalEngine::doPhysicalProcessing"<<endl;
    // !debug

    // In this example, X coordinate of the robot location would be changed
    // robot_->currentLocationX += 2.;

    // In this example, the robot will move to the next node of the path found
    //if(!path.empty()){
    //    auto p = path.front();
    //    robot_->currentLocationX = p->robot_config_.x;
    //    robot_->currentLocationY = p->robot_config_.y;
    //    cout <<"robot moving" <<endl;
    //    path.pop_front();
    //} else {
    //    cout <<"robot arrived at target" <<endl;
    //}


    return 1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// data aquisition and restore
void PhysicalEngine::DataProcessingBeforeEvent()
{
    return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// data aquisition and restore
void PhysicalEngine::DataProcessingInEvent()
{
    return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// data aquisition and restore
void PhysicalEngine::DataProcessingAfterEvent()
{
    return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// verbose Level
void PhysicalEngine::setVerboseLevel(int verboseLevel_)
{
    verboseLevel = verboseLevel_;

    return;
}
