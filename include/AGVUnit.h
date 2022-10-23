#ifndef AGVUnit_H
#define AGVUnit_H

#include "AbstractRobotUnit.h"

class AGVUnit: virtual public AbstractRobotUnit
{
	// variables that the AGV has
	public:
		string laserBrandName;

	public:
		AGVUnit();
		~AGVUnit();

	public:
		void test();

	public:
		void showAllParameters();
};

#endif // AGVUnit_H

