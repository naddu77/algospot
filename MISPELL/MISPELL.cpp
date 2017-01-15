// MISPELL.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>

using namespace std;

int main()
{
	int count;
	cin >> count;
	int index = 1;
	while (count--)
	{
		int position;
		string str;
		cin >> position >> str;
		str.erase(position - 1, 1);
		cout << index << " " << str << endl;
		index++;
	}
    return 0;
}

