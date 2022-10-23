#ifndef ABSTRACTTARGETUNIT_H
#define ABSTRACTTARGETUNIT_H

#include <iostream>
#include <string>

using namespace std;

class AbstractTargetUnit
{
    // Target variables written here
    public:
        // target name
        string targetName;

        // target ID
        int targetID;

        // location
        double currentLocationX;
        double currentLocationY;
        double currentLocationZ;

    public:
        // a test function
        virtual void test() = 0;

    public:
        // show all parameters
        virtual void showAllParameters() = 0;
};

#endif // ABSTRACTTATGETUNIT_H
