// WEIRD.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

bool IsWeirdNumber(const int input, const vector<int>& divisors, int n, int prev_sum = 0)
{
	for (int i = n; i >= 0 ; --i)
	{
		int sum = prev_sum + divisors[i];
		if (sum > input)
			continue;

		if (input == sum)
			return false;

		if (!IsWeirdNumber(input, divisors, i - 1, sum))
			return false;
	}

	return true;
}

int main()
{
	int count;
	cin >> count;
	while (count--)
	{
		int input;
		cin >> input;
		vector<int> divisors;
		for(auto i = 1 ; i <= (input >> 1); ++i)
		{
			if (input % i == 0)
			{
				divisors.push_back(i);
			}
		}

		if (IsWeirdNumber(input, divisors, divisors.size() - 1))
		{
			if (accumulate(divisors.begin(), divisors.end(), 0) > input)
				cout << "weird" << endl;
			else
				cout << "not weird" << endl;
		}
		else
			cout << "not weird" << endl;
	}

    return 0;
}

