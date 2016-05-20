#ifndef COMPARATOR_STRATEGY_H
#define COMPARATOR_STRATEGY_H
#include "ModelForIdealCycles.h"

class ComparatorStrategy
{
public:
	void setRawData(ModelForIdealCycles data);
	void virtual compare() = 0;
private:
	ModelForIdealCycles data;
};

#endif