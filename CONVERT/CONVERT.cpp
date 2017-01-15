// CONVERT.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
	map<string, pair<double, string>> conversion_table;
	conversion_table.insert(make_pair("kg", make_pair(2.2046, "lb")));
	conversion_table.insert(make_pair("lb", make_pair(0.4536, "kg")));
	conversion_table.insert(make_pair("l", make_pair(0.2642, "g")));
	conversion_table.insert(make_pair("g", make_pair(3.7854, "l")));
	
	int count;
	cin >> count;

	int index = 1;
	while (count--)
	{
		double number;
		string unit;

		cin >> number >> unit;

		pair<double, string> data = conversion_table.at(unit);

		cout << fixed;
		cout.precision(4);
		cout << index << " " << number * data.first << " " << data.second << endl;

		index++;
	}

    return 0;
}

