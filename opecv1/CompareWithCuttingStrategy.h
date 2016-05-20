#include "ComparatorStrategy.h"
class CompareWithCuttingStrategy : ComparatorStrategy
{
public:
	void compare();
	CompareWithCuttingStrategy();
	CompareWithCuttingStrategy(ModelForIdealCycles data);
	~CompareWithCuttingStrategy();
private:
	ModelForIdealCycles data;
};
