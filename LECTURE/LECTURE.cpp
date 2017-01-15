// LECTURE.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int count;
	cin >> count;

	for (auto i = 0; i < count; ++i)
	{
		string input;
		cin >> input;
		vector<string> tokens;
		for (auto iter = input.begin(); iter != input.end(); iter = iter + 2)
		{
			string temp;
			temp.assign(iter, iter + 2);
			tokens.push_back(move(temp));
		}
		sort(tokens.begin(), tokens.end(), [](const string& left, const string& right) { return left < right; });
		for_each(tokens.begin(), tokens.end(), [](const string& data) {cout << data; });
		cout << endl;
	}

    return 0;
}

