#include "AGVUnit.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
AGVUnit::AGVUnit()
{
	// Initialize AGV variables
	robotName = "AGV_NoName";
	robotID = -1;

	currentLocationX = 0;
	currentLocationY = 0;
	currentLocationZ = 0;

	currentLocationX = 0;
	currentLocationY = 0;
	currentLocationZ = 0;

	currentVx = 0;
	currentVy = 0;
	currentVz = 0;

	currentAx = 0;
	currentAy = 0;
	currentAz = 0;

	currentBatteryLevel = 0;

	currentSizeLength = 0;
	currentSizeWidth  = 0;
	currentSizeHeight = 0;

    path.clear();

	laserBrandName = "SICK";


	// !Initialize AGV variables

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
AGVUnit::~AGVUnit()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void AGVUnit::test()
{
	cout<<"Hello, this is class AGVUnit."<<endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void AGVUnit::showAllParameters()
{
	cout<<""<<endl;
	cout<<"--------------------"<<endl;

	cout<<"robotName: "<<robotName<<endl;
	cout<<"robotID: "<<robotID<<endl;

	cout<<"currentLocationX: "<<currentLocationX<<endl;
	cout<<"currentLocationY: "<<currentLocationY<<endl;
	cout<<"currentLocationZ: "<<currentLocationZ<<endl;

	cout<<"currentOrientationRx: "<<currentOrientationRx<<endl;
	cout<<"currentOrientationRy: "<<currentOrientationRy<<endl;
	cout<<"currentOrientationRz: "<<currentOrientationRz<<endl;

	cout<<"currentVx: "<<currentVx<<endl;
	cout<<"currentVy: "<<currentVy<<endl;
	cout<<"currentVz: "<<currentVz<<endl;

	cout<<"currentAx: "<<currentAx<<endl;
	cout<<"currentAy: "<<currentAy<<endl;
	cout<<"currentAz: "<<currentAz<<endl;

	cout<<"currentBatteryLevel: "<<currentBatteryLevel<<endl;

	cout<<"currentSizeLength: "<<currentSizeLength<<endl;
	cout<<"currentSizeWidth : "<<currentSizeWidth <<endl;
	cout<<"currentSizeHeight: "<<currentSizeHeight<<endl;

	cout<<"laserBrandName: "<<laserBrandName<<endl;
}
