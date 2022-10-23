#include "BasicPhysicalEngine.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
BasicPhysicalEngine::BasicPhysicalEngine(double timeStart_, double timeEnd_, double timeWidth_)
: PhysicalEngine(timeStart_, timeEnd_, timeWidth_)
{
    DM = new BasicDecisionMaking("Basic Decistion Making");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
BasicPhysicalEngine::~BasicPhysicalEngine()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// step 1 : get the task, do decision making
int BasicPhysicalEngine::doDecisionMaking()
{
	//
	// BasicDecisionMaking
	//
    //BasicDecisionMaking DM("Basic Decistion Making");

    DM->showAllParameters();

    //DM->setATaskUnit(taskUnit); //!!!!!!!!!!!!!!!!

    int isTaskAllocationGood = DM->doTaskAllocation();
    int isPathPlanningGood = DM->doPathPlanning();

    return 1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// get the task from outside
int BasicPhysicalEngine::fluctuateTaskUnit()
{
    // In this function, the task would be changed according to the needs from outside.
    // Such as fluctuations to the robots. For instance, the slightly change in the location of the robot.

    // In this example, nothing would be fluctuated.

    return 1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Physical Processing
// Do Physical Processing
int BasicPhysicalEngine::doPhysicalProcessing(AbstractRobotUnit* robot_)
{

    // In this function, the robot would be processed.

    // debug
    //cout<<".... Pay attention : this is BasicPhysicalEngine::doPhysicalProcessing"<<endl;
    // !debug

    // In this example, X coordinate of the robot location would be changed
    // robot_->currentLocationX += 2.;

    // In this example, the robot will move to the next node of the path found
    if(!robot_->path.empty()){
        //robot_->currentLocationX = robot_->path.front()->robot_config_.x;
        //robot_->currentLocationY = robot_->path.front()->robot_config_.y;

        //cout <<"robot moving" <<endl;

        robot_->path.pop_front();

        // set a new location for the robot
        if(!robot_->path.empty())
        {
            robot_->currentLocationX = robot_->path.front()->robot_config_.x;
            robot_->currentLocationY = robot_->path.front()->robot_config_.y;
        }
        else
        {
            cout <<"robot arrived at target" <<endl;
        }

        //cout<<"robot location : "<<robot_->currentLocationX<<", "<<robot_->currentLocationY<<endl;

    }
    //else
    //{
    //    cout <<"robot arrived at target" <<endl;
    //}


    return 1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// data aquisition and restore
void BasicPhysicalEngine::DataProcessingBeforeEvent()
{
    cout<<"BasicPhysicalEngine::DataProcessingBeforeEvent()..."<<endl;

    // create a new file
    writeFile.open("outputData_robotInfo.txt");


    return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// data aquisition and restore
void BasicPhysicalEngine::DataProcessingInEvent()
{
    //cout<<"BasicPhysicalEngine::DataProcessingInEvent()..."<<endl;
    
    // write robot info 
    for(int i=0;i<DM->taskUnit->robotList.size();i++)
    {
        // get time 
        writeFile<<to_string(timeLoopID)<<" ";

        // get name
        string robotName = DM->taskUnit->robotList[i]->robotName;
        writeFile<<robotName<<" ";


        // get location 
        double x = DM->taskUnit->robotList[i]->currentLocationX;
        double y = DM->taskUnit->robotList[i]->currentLocationY;

        writeFile<<to_string(x)<<" ";
        writeFile<<to_string(y)<<" ";

        writeFile<<endl;
    }


    return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// data aquisition and restore
void BasicPhysicalEngine::DataProcessingAfterEvent()
{
    cout<<"BasicPhysicalEngine::DataProcessingAfterEvent()..."<<endl;

    writeFile.close();

    return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// task unit
void BasicPhysicalEngine::setATaskUnit(AbstractTaskUnit* taskUnit_)
{
    DM->setATaskUnit(taskUnit_); 

    isTaskUnitSet = true;

    // debug
    //cout<<"$$$$$$$BasicPhysicalEngine::setATaskUnit"<<endl;
    //DM->taskUnit->showAllParameters();
    // !debug

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// set the task
void BasicPhysicalEngine::setTheMap(std::vector<std::vector<int>> map_)
{

    DM->setTheMap(map_); 

}
