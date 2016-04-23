#include "ComparatorStrategy.h"
class CompareWithCuttingStrategy : ComparatorStrategy
{
public:
	void compare();
	CompareWithCuttingStrategy();
	CompareWithCuttingStrategy(IdealCycle data);
	~CompareWithCuttingStrategy();
private:
	IdealCycle data;
};
