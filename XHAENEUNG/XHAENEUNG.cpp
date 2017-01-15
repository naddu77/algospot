// XHAENEUNG.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>

using namespace std;

int main()
{
	const unordered_map<string, int> converstion_table = {
		make_pair("zero", 0),
		make_pair("one", 1),
		make_pair("two", 2),
		make_pair("three", 3),
		make_pair("four", 4),
		make_pair("five", 5),
		make_pair("six", 6),
		make_pair("seven", 7),
		make_pair("eight", 8),
		make_pair("nine", 9),
		make_pair("ten", 10)
	};

	const unordered_map<int, string> converstion_table2 = {
		make_pair(0, "zero"),
		make_pair(1, "one"),
		make_pair(2, "two"),
		make_pair(3, "three"),
		make_pair(4, "four"),
		make_pair(5, "five"),
		make_pair(6, "six"),
		make_pair(7, "seven"),
		make_pair(8, "eight"),
		make_pair(9, "nine"),
		make_pair(10, "ten")
	};

	const unordered_map<string, function<int(int, int)>> function_table = {
		make_pair("+", [](int lhs, int rhs) {return lhs + rhs; }),
		make_pair("-", [](int lhs, int rhs) {return lhs - rhs; }),
		make_pair("*", [](int lhs, int rhs) {return lhs * rhs; })
	};

	int count;
	cin >> count;

	while (count--)
	{
		string A, operation, B, equal, C;
		cin >> A >> operation >> B >> equal >> C;
		function<int(int, int)> func = function_table.at(operation);
		int result = func(converstion_table.at(A), converstion_table.at(B));
		if (result >= 0 && result <= 10)
		{
			string actual_C = converstion_table2.at(result);

			if (actual_C.size() == C.size())
			{
				for (auto a : actual_C)
				{
					size_t pos = C.find_first_of(a);
					if (pos != string::npos)
						C.erase(pos, 1);
				}

				if (C.empty())
					cout << "Yes" << endl;
				else
					cout << "No" << endl;
			}
			else
			{
				cout << "No" << endl;
			}
		}
		else
		{
			cout << "No" << endl;
		}
		
	}

    return 0;
}

