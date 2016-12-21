#include <iostream>
#include "Board.h"
#include "DynamicArray.h"

void printDynamicArray(DynamicArray<float>& dynArr)
{
	for (int i = 0; i < dynArr.getLength(); i++)
	{
		std::cout << "Element " << i << ":" << dynArr[i] << " Array Length: " << dynArr.getLength() << std::endl;
	}
}

int main()
{
	// 	{
	// 		Board board;
	// 		board.render();
	// 	}

	DynamicArray<float> da1;
	da1.add(100.0f);
	da1.add(200.0f);
	da1.add(0.01f);
	da1.add(10.0f);

	//printDynamicArray(da1);

	da1.add(1.0f);
	da1.add(2.0f);
	da1.add(3.0f);
	da1.add(4.0f);
	da1.add(5.0f);
	da1.add(6.0f);

	//printDynamicArray(da1);

	da1.add(7.0f);

	printDynamicArray(da1);

	char tmp;
	std::cin >> tmp;
	return 0;
}