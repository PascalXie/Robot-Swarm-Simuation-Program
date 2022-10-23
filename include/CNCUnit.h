#ifndef CNCUNIT_H
#define CNCUNIT_H

#include "AbstractTargetUnit.h"

class CNCUnit : virtual public AbstractTargetUnit
{
	// CNC parameters
	public:
		string PLCBrandName;

	public:
		CNCUnit();
		~CNCUnit();

	public:
		// a test function
		void test();

	public:
		// show all parameters
		void showAllParameters();

};

#endif // CNCUNIT_H

