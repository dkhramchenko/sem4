#include <iostream>
#include "Set.h"

using namespace std;

int main()
{
	Set set;

	set.addValueByKey("1", "1");
	set.addValueByKey("15", "15");
	set.addValueByKey("7", "7");
	set.addValueByKey("2", "2");
	set.addValueByKey("3", "3");

	cout << "tree:" << endl << endl;
	set.print();
	cout << endl;
	cout << "element with key 15 = " << set.getValueByKey("15") << endl << endl;

	cout << "height = " << set.getElementHeightByKey("15") << endl;
	return 0;
}