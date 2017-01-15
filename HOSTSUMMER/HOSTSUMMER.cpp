// HOSTSUMMER.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main()
{
	int count;
	cin >> count;
	while (count--)
	{
		int goal_of_power_consumption;
		cin >> goal_of_power_consumption;
		vector<int> A(9);
		for (auto i = 0; i < 9; ++i)
			cin >> A[i];
		if (accumulate(A.begin(), A.end(), 0) <= goal_of_power_consumption)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
    return 0;
}

