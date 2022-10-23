#include "BasicDecisionMaking.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
BasicDecisionMaking::BasicDecisionMaking(string decisionMakingName_)
{
    decisionMakingName = decisionMakingName_;

    isTaskUnitSet = false;
    isMapSet = false;


    dosePathPlanningConsiderRobotAsObstacle = true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
BasicDecisionMaking::~BasicDecisionMaking()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void BasicDecisionMaking::showAllParameters()
{
    cout<<"\n"<<endl;
    cout<<"----"<<endl;
    cout<<"This is BasicDecisionMaking::showAllParameters()"<<endl;
    cout<<"decisionMakingName: "<<decisionMakingName<<endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Do Decision making
// part 1 : task allocation
int BasicDecisionMaking::doTaskAllocation()
{
    // step 0 : check if the task unit exist
    if(!isTaskUnitSet)
    {
        cout<<"\n"<<endl;
        cout<<"BasicDecisionMaking::doTaskAllocation"<<endl;
        cout<<"The task unit dose not exist!"<<endl;
        return 0;
    }

    // step 0 : initiate the robotTargetPairList
    taskUnit->robotTargetPairList.clear();

    // step 1 : get all robots
    int sizeRobots = taskUnit->robotList.size();
    int sizeTargets = taskUnit->targetList.size();
    if(sizeRobots<sizeTargets)
    {
        for(int i=0;i<sizeRobots;i++)
        {
            taskUnit->robotTargetPairList.push_back(i);
        }
    }

    if(sizeRobots>=sizeTargets)
    {
        for(int i=0;i<sizeTargets;i++)
        {
            taskUnit->robotTargetPairList.push_back(i);
        }
        for(int i=0;i<sizeRobots-sizeTargets;i++)
        {
            taskUnit->robotTargetPairList.push_back(-1); // -1 represents no target
        }
    }




    return 1;
}

// part 2 : path planning for all robots
int BasicDecisionMaking::doPathPlanning()
{
    // debug
    //cout<<"Debug: BasicDecisionMaking::doPathPlanning "<<endl;
    // !debug

    // step 0 : check if the map exist
    if(!isMapSet)
    {
        cout<<"\n"<<endl;
        cout<<"BasicDecisionMaking::doPathPlanning"<<endl;
        cout<<"The map dose not exist!"<<endl;
        return 0;
    }

    // show the map
    //for(int i=0; i<map.size(); i++) // x represents the row ID
    //{
    //    for(int j=0; j<map[0].size(); j++) // y represents the columm ID
    //    {
    //        cout<<map[i][j]<<" ";
    //    }
    //    cout<<endl;
    //}

    // step 1 : start a loop for all robots
    int sizeRobots = taskUnit->robotList.size();
    //cout<<"11111"<<endl;
    //cout<<"sizeRobots: "<<sizeRobots<<endl;

    for(int i=0;i<sizeRobots;i++)
    {
        // initiate the map
        std::vector<std::vector<int>> mapCurrent = map;

        // get robotID, the robot ID is the index i
        int robotID = i;

        // initiate the map
        A_star astar;


        if(dosePathPlanningConsiderRobotAsObstacle)
        {
            //cout<<"Path Planning would Consider Robots As Obstacles"<<endl;

            // set current positions of the other robots as obstacles
            for(int j=0; j<sizeRobots; j++)
            {
                int otherRobotID = j;

                if(otherRobotID==robotID) continue;

                float xCur = taskUnit->robotList[otherRobotID]->currentLocationX;
                float yCur = taskUnit->robotList[otherRobotID]->currentLocationY;

                //cout<<"@@@@@@@@@@@@@@@"<<endl;
                //cout<<"obstacle x,y: "<<xCur<<", "<<yCur<<endl;

                mapCurrent[xCur][yCur] = 1;

            }

            // set the near far path of the other robots as the obstacles
            for(int j=0; j<robotID; j++)
            //for(int j=0; j<sizeRobots; j++)
            {
                int otherRobotID = j;

                int timeStepCounter = 0;
                for (auto &p : taskUnit->robotList[otherRobotID]->path)
                {
                    if(timeStepCounter>2)
                    {
                        break;
                    }

                    float pathxCur = p->robot_config_.x;
                    float pathyCur = p->robot_config_.y;

                    mapCurrent[pathxCur][pathyCur] = 1;

                    timeStepCounter ++;

                }

            }
        }
        //showTheMap(mapCurrent);

        astar.init_map(mapCurrent);

        // step 2 : make sure the current robot and the target it serves
        int targetID = taskUnit->robotTargetPairList[robotID];

        //set start node and end node for A*
        RobotConfiguration start_config_;
        start_config_.x = taskUnit->robotList[robotID]->currentLocationX;
        start_config_.y = taskUnit->robotList[robotID]->currentLocationY;

        Priority start_pri_;
        start_pri_.g = 0;
        start_pri_.h = 0;
        start_pri_.f = 0;

        Node start_node = Node(start_config_, start_pri_);

        // get the target of the current robot
        int TargetID = taskUnit->robotTargetPairList[robotID];
        if(TargetID==-1)
        {
            cout<<"Current Robot has not been allocated with a target"<<endl;
            return 1;
        }
        if(TargetID<0||TargetID>taskUnit->targetList.size()-1)
        {
            cout<<"some thing wrong happened in BasicDecisionMaking::doPathPlanning!"<<endl;
            return 0;
        }

        RobotConfiguration end_config_;
        //end_config_.x = 3;
        //end_config_.y = 3;
        end_config_.x = taskUnit->targetList[TargetID]->currentLocationX;
        end_config_.y = taskUnit->targetList[TargetID]->currentLocationY;

        Priority end_pri_;
        end_pri_.g = 0;
        end_pri_.h = 0;
        end_pri_.f = 0;

        Node end_node = Node(end_config_, end_pri_);

        // A*
        //std::list<Node *> path = astar.get_path(start_node, end_node, false);
        list<std::shared_ptr<Node>> path = astar.get_path(start_node, end_node, false);

        // print path found
        //for (auto &p : path) {
        //  std::cout << "(" << p->robot_config_.x << "," << p->robot_config_.y << ") ";
        //}
        //std::cout << "\n";

        // set the path to the robot
        taskUnit->robotList[robotID]->setPath(path);

    }




    return 1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//tools for map
void BasicDecisionMaking::showTheMap(std::vector<std::vector<int>> map_)
{
    for(int i=0; i<map_.size(); i++) // x represents the row ID
    {
        for(int j=0; j<map_[0].size(); j++) // y represents the columm ID
        {
            cout<<map_[i][j]<<" ";
        }
        cout<<endl;
    }
}
