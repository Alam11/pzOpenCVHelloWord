#include "IdealCycle.h"
class SignumComparatorStrategy
{
public:
	void setRawData(IdealCycle data);
	void compare();
	SignumComparatorStrategy();
	SignumComparatorStrategy(IdealCycle data);
	~SignumComparatorStrategy();
private:
	IdealCycle data; 
};

