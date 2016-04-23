#include "ComparatorStrategy.h"
class SignumComparatorStrategy : ComparatorStrategy
{
public:
	void compare();
	SignumComparatorStrategy();
	SignumComparatorStrategy(IdealCycle data);
	~SignumComparatorStrategy();
private:
	IdealCycle data; 
};

