#include "CNCUnit.h"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CNCUnit::CNCUnit()
{
	// Initialize paramters of CNCUnit
	targetName = "Target_NoName";
	targetID = -1;

    currentLocationX = 0;
    currentLocationY = 0;
    currentLocationZ = 0;

	PLCBrandName = "CNC_NoName";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CNCUnit::~CNCUnit()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CNCUnit::test()
{
	cout<<"Hello, this is class CNCUnit"<<endl;
	cout<<"this is function test"<<endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CNCUnit::showAllParameters()
{
	cout<<""<<endl;
	cout<<"-----------------------------"<<endl;

	cout<<"targetName: "<<targetName<<endl;
	cout<<"targetID: "<<targetID<<endl;

    cout<<"currentLocationX: "<<currentLocationX<<endl;
    cout<<"currentLocationY: "<<currentLocationY<<endl;
    cout<<"currentLocationZ: "<<currentLocationZ<<endl;

	cout<<"PLCBrandName: "<<PLCBrandName<<endl;
}
