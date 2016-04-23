#ifndef COMPARATOR_STRATEGY_H
#define COMPARATOR_STRATEGY_H
#include "IdealCycle.h"

class ComparatorStrategy
{
public:
	void setRawData(IdealCycle data);
	void virtual compare() = 0;
private:
	IdealCycle data;
};

#endif