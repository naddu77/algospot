// ENCRYPT.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>

using namespace std;

int main()
{
	int count;
	cin >> count;
	while (count--)
	{
		string input;
		cin >> input;
		for (auto i = 0; i < input.size(); i += 2)
			cout << input[i];
		for (auto i = 1; i < input.size(); i += 2)
			cout << input[i];
		cout << endl;
	}

    return 0;
}

