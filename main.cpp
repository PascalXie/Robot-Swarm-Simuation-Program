#include <iostream>
#include <random>

#include "AGVUnit.h"
#include "CNCUnit.h"
#include "LoadingTaskUnit.h"
#include "BasicPhysicalEngine.h"

using namespace std;

void GenerateABolckInMap(int xCentor, int yCentor, int halfSizeBlock, int Map_Maxx, int Map_Maxy, vector<vector<int>> &map)
{

    for(int i=0; i<halfSizeBlock*2+1; i++)
    for(int j=0; j<halfSizeBlock*2+1; j++)
    {
        int x = xCentor - halfSizeBlock + i;
        int y = yCentor - halfSizeBlock + j;

        if(x<0||x>Map_Maxx-1)
            continue;

        if(y<0||y>Map_Maxy-1)
            continue;

        int marginWidth = 3;
        if(x<0+marginWidth||x>Map_Maxx-1-marginWidth)
            continue;

        if(y<0+marginWidth||y>Map_Maxy-1-marginWidth)
            continue;

        map[x][y]  = 1;
    }

}

void GenerateMapRandomly(int Map_Maxx, int Map_Maxy, int SizeObstaclesInMap, vector<vector<int>> &map)
{
    // step 0 : prepare the random number generator 
    default_random_engine random(time(NULL));
    uniform_int_distribution<int> disx(1+2, Map_Maxx-1-3);
    uniform_int_distribution<int> disy(1+2, Map_Maxy-1-3);

    // step 1 : initiate a map
    map.clear();

    for(int i=0; i<Map_Maxx; i++) // x represents the row ID
    {
        vector<int> currentRow;
        for(int j=0; j<Map_Maxy; j++) // y represents the columm ID
        {
            //int isObstacle = dis(random);
            int isObstacle = 0;

            if(i==0||i==Map_Maxx-1) isObstacle=1;
            if(j==0||j==Map_Maxy-1) isObstacle=1;

            currentRow.push_back(isObstacle);
        }
        map.push_back(currentRow);
    }

    // set obstacles

    //// method 1 : generate a pixel once atime
    //for(int i=0; i<SizeObstaclesInMap; i++)
    //{
    //    int x = disx(random);
    //    int y = disy(random);

    //    GenerateABolckInMap();

    //    map[x][y]  = 1;
    //}

    // method 2 : generate a block of pixles once a time
    for(int i=0; i<SizeObstaclesInMap; i++)
    {
        int xCentor = disx(random);
        int yCentor = disy(random);

        int halfSizeBlock = 3;

        GenerateABolckInMap(xCentor, yCentor, halfSizeBlock, Map_Maxx, Map_Maxy, map);
    }

    // show the map
    //for(int i=0; i<Map_Maxx; i++) // x represents the row ID
    //{
    //    for(int j=0; j<Map_Maxy; j++) // y represents the columm ID
    //    {
    //        cout<<map[i][j]<<" ";
    //    }
    //    cout<<endl;
    //}

    // write the map into a file
    ofstream fileMap("output_map.txt");

    for(int i=0; i<Map_Maxx; i++) // x represents the row ID
    {
        for(int j=0; j<Map_Maxy; j++) // y represents the columm ID
        {
            fileMap<<map[i][j]<<" ";
        }
        fileMap<<endl;
    }

    fileMap.close();

}

void example()
{
    cout<<"Example"<<endl;

    // step 0 : set the time for physical engine
	double timeStart = 0;
    double timeEnd   = 800;
	double timeWidth = 1;

    // step 0 : set the map, robots and targets randomly
    int Map_Maxx = 100;
    int Map_Maxy = 100;

    int SizeRobots  = 30;
    int SizeTargets = 30;

    int SizeObstaclesInMap = Map_Maxx*Map_Maxy/200;

    //
    // generate a task unit  
    //
    AbstractTaskUnit *loadingTask = new LoadingTaskUnit();

    //
    // genreate agv
    //
    for(int i=0;i<SizeRobots;i++)
    {
        AbstractRobotUnit *agv = new AGVUnit();
        agv->robotName = "agv" + to_string(i);
        agv->currentLocationX = 1 + (int) (i/(Map_Maxy-2));
        agv->currentLocationY = 1 + (int) (i%(Map_Maxy-2));
        agv->showAllParameters();

        loadingTask->addARobot(agv);
    }

    //
    // generate CNC units 
    //

    for(int i=0; i<SizeTargets; i++)
    {

        AbstractTargetUnit *cnc = new CNCUnit();
        cnc->targetName = "CNC" + to_string(i);
        cnc->currentLocationX = Map_Maxx - (1 + (int) i/(Map_Maxy-2) + 1);
        cnc->currentLocationY = Map_Maxy - (1 + (int) i%(Map_Maxy-2) + 1);
        cnc->showAllParameters();

        loadingTask->addATarget(cnc);
    }

    // debug
    loadingTask->showAllParameters();

    // generate a map
    vector<vector<int>> map;
    GenerateMapRandomly(Map_Maxx, Map_Maxy, SizeObstaclesInMap, map);

	//
	// PhysicalEngine
	//
	BasicPhysicalEngine PE(timeStart, timeEnd, timeWidth);

    PE.setATaskUnit(loadingTask);

    PE.setTheMap(map);

    PE.setVerboseLevel(1);

    // step 2 : start simulation
    PE.startSimulation();



}

int main()
{
    cout<<"Hello"<<endl;

    example();

    return 1;
}
