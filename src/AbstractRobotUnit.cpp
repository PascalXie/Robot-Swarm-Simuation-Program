#include "AbstractRobotUnit.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
AbstractRobotUnit::AbstractRobotUnit()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
AbstractRobotUnit::~AbstractRobotUnit()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// A*
// set the path
void AbstractRobotUnit::setPath(std::list<std::shared_ptr<Node>> path_)
{
    path = path_;
}
