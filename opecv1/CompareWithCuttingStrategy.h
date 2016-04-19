#include "IdealCycle.h"
class CompareWithCuttingStrategy
{
public:
	void setRawData(IdealCycle data);
	void compare();
	CompareWithCuttingStrategy();
	CompareWithCuttingStrategy(IdealCycle data);
	~CompareWithCuttingStrategy();
private:
	IdealCycle data;
};
