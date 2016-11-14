#include "IntArray.h"

#define PRINT(msg) std::cout << msg << std::endl;

using namespace std;

int main()
{
	IntArray arr1;
	PRINT(arr1.getLength());

	IntArray arr2(15);
	PRINT(arr2.getLength());

	char in;
	cin >> in;
	return 0;
}