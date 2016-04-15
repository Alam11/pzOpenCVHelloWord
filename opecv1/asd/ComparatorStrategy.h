#include "IdealCycle.h"
#include <iostream>

class ComparatorStrategy
{
public:
	void setModel(IdealCycle data);
	virtual void compare() = 0;
	ComparatorStrategy();
	~ComparatorStrategy();
};


