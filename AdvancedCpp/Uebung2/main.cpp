#include "IntArray.h"
#include <conio.h>

using namespace std;

int main()
{
	IntArray arr1;
	PRINT(arr1.getLength());

	IntArray arr2(15);
	PRINT(arr2.getLength());
	PRINT("---------------");
	PRINT("Before Erase");
	arr1.append(1);
	arr1.append(2);
	arr1.append(3);
	arr1.append(4);
	arr1.append(5);
	PRINTARRAY(arr1, arr1.getLength());
	PRINT("After Erase");
	arr1.erase(0);
	arr1.erase(3);
	for (int i = 0; i < arr1.getLength(); i++)
	{
		PRINT(arr1[i]);
	}


	_getch();
	return 0;
}