#include "IntArray.h"

#define PRINT(msg) std::cout << msg << std::endl;

using namespace std;

int main()
{
	IntArray arr1;
	PRINT(arr1.getLength());

	IntArray arr2(15);
	PRINT(arr2.getLength());
	arr1.append(10);
	arr1.append(5);
	arr1.append(1);
	for (int i = 0; i < arr1.getLength(); i++)
	{
		PRINT(arr1[i]);
	}

	char in;
	cin >> in;
	return 0;
}