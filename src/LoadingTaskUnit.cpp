#include "LoadingTaskUnit.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
LoadingTaskUnit::LoadingTaskUnit()
{
    taskName = "Task_NoName";
    taskID = -1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
LoadingTaskUnit::~LoadingTaskUnit()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void LoadingTaskUnit::showAllParameters()
{
    cout<<"\n"<<endl;
    cout<<"-----------------------------"<<endl;
    cout<<"class LoadingTaskUnit, showAllParameters"<<endl;
    cout<<"taskName: "<<taskName<<endl;
    cout<<"taskID: "<<taskID<<endl;

    //int sizeRobotList = robotIDList.size();
    //if(sizeRobotList==0)
    //{
    //    cout<<"robotList has no element"<<endl;
    //}
    //else
    //{
    //    cout<<"robotList has "<< sizeRobotList <<" element"<<endl;
    //}

    //int sizeTargetList = targetIDList.size();
    //if(sizeTargetList==0)
    //{
    //    cout<<"targetList has no element"<<endl;
    //}
    //else
    //{
    //    cout<<"targetList has "<< sizeTargetList <<" element"<<endl;
    //}

    int sizeRobotList = robotList.size();
    if(sizeRobotList==0)
    {
        cout<<"robotList has no element"<<endl;
    }
    else
    {
        cout<<"robotList has "<< sizeRobotList <<" element"<<endl;
    }

    int sizeTargetList = targetList.size();
    if(sizeTargetList==0)
    {
        cout<<"targetList has no element"<<endl;
    }
    else
    {
        cout<<"targetList has "<< sizeTargetList <<" element"<<endl;
    }


    //
    for(int i=0; i<robotTargetPairList.size();i++)
    {
        cout<<"robotTargetPairList: Robot ID: "<<i<<"; Target ID: "<<robotTargetPairList[i]<<endl;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int LoadingTaskUnit::addARobotID(int ID)
{
    robotIDList.push_back(ID);

    return 1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int LoadingTaskUnit::addATargetID(int ID)
{
    targetIDList.push_back(ID);

    return 1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int LoadingTaskUnit::addARobot(AbstractRobotUnit* agv)
{
    robotList.push_back(agv);
    robotIDList.push_back(agv->robotID);

    // debug
    //cout<<"@@@@@@@@@@@@@@This is LoadingTaskUnit::addARobot"<<endl;
    //agv->showAllParameters();
    //cout<<"@@@@@@@@@@@@@@This is LoadingTaskUnit::addARobot"<<endl;

    //cout<<"robotList.size(): "<<robotList.size()<<endl;

    //showAllParameters();

    //cout<<"@@@@@@@@@@@@@@This is LoadingTaskUnit::addARobot"<<endl;
    // !debug


    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int LoadingTaskUnit::addATarget(AbstractTargetUnit* cnc)
{
    targetList.push_back(cnc);
    targetIDList.push_back(cnc->targetID);

    // debug
    //cout<<"This is LoadingTaskUnit::addATarget"<<endl;
    //cnc->showAllParameters();
    // !debug

    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// set the robot-target pairs
int LoadingTaskUnit::setRobotTargetPairList()
{
    // debug
    cout<<"This is LoadingTaskUnit::setRobotTargetPairList"<<endl;
    // !debug

    return 1;
}
