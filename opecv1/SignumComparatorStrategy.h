#include "ComparatorStrategy.h"
class SignumComparatorStrategy : ComparatorStrategy
{
public:
	void compare();
	SignumComparatorStrategy();
	SignumComparatorStrategy(ModelForIdealCycles data);
	~SignumComparatorStrategy();
private:
	ModelForIdealCycles data; 
};

