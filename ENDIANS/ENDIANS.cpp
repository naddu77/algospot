// ENDIANS.cpp : Defines the entry point for the console application.
//

#include <iostream>

typedef union
{
	unsigned int n;
	unsigned char byte[4];
} data;

int main()
{
	int count;
	std::cin >> count;

	while (count--)
	{
		data input;
		
		std::cin >> input.n;

		data output;
		output.byte[3] = input.byte[0];
		output.byte[2] = input.byte[1];
		output.byte[1] = input.byte[2];
		output.byte[0] = input.byte[3];
		std::cout << output.n << std::endl;
	}

    return 0;
}

