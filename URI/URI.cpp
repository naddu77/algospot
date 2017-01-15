// URI.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main()
{
	const unordered_map<string, string> conversion_table = {
		make_pair("%20", " "),
		make_pair("%21", "!"),
		make_pair("%24", "$"),
		make_pair("%25", "%"),
		make_pair("%28", "("),
		make_pair("%29", ")"),
		make_pair("%2a", "*")
	};

	int count;
	cin >> count;
	while (count--)
	{
		string input;
		cin >> input;
		for (auto iter = input.begin(); iter != input.end(); ++iter)
		{
			if (*iter == '%')
			{
				string temp;
				temp.assign(iter, iter + 3);
				input.replace(iter, iter + 3, conversion_table.at(temp));
			}
		}
		cout << input << endl;;
	}

    return 0;
}

