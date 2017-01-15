// CLOCKSYNC.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <assert.h>
#include <algorithm>

using namespace std;

class ClockSync
{
public:
	ClockSync() = delete;
	ClockSync(const vector<int>& times)
	{
		for (auto time : times)
		{
			this->times.emplace_back(time % 12);	// 계산의 편의성을 위해 데이터 정규화(12시를 0시로)
		}
	}

	bool DoAlgorithm(int switch_number = 0)
	{
		if (all_of(times.begin(), times.end(), [](int time) { return time == 0; }))
			return true;
		
		if (switch_number >= 10)
			return false;

		SwitchClocks(switch_number);
		result++;
		if (DoAlgorithm(switch_number + 1))
			return true;
		SwitchClocks(switch_number);
		result++;
		if (DoAlgorithm(switch_number + 1))
			return true;
		SwitchClocks(switch_number);
		result++;
		if (DoAlgorithm(switch_number + 1))
			return true;
		SwitchClocks(switch_number);
		result -= 3;
		if (DoAlgorithm(switch_number + 1))
			return true;
	
		return false;
	}

	int GetResult(void) const
	{
		return result;
	}

	~ClockSync() = default;

private:
	int result = 0;
	vector<int> times;
	static const array<vector<int>, 10> switching_table;
	array<vector<int>, 16> linked_switchs;

	void SwitchClocks(int switch_index)
	{
		assert(switch_index >= 0 && switch_index < 10);
		for (auto clock_number : switching_table[switch_index])
			SwitchClock(clock_number);
		
	}

	void SwitchClock(int clock_number)
	{
		assert(clock_number >= 0 && clock_number < 16);
		times[clock_number] += 3;
		times[clock_number] %= 12;
	}

	bool IsValid(const vector<int>& time_vector) const
	{
		return all_of(time_vector.begin(), time_vector.end(), [](int time) { return time == 0; });
	}


};

const array<vector<int>, 10> ClockSync::switching_table = {
	vector<int>{0,1,2},
	vector<int>{3,7,9,11},
	vector<int>{4,10,14,15},
	vector<int>{0,4,5,6,7},
	vector<int>{6,7,8,10,12},
	vector<int>{0,2,14,15},
	vector<int>{3,14,15},
	vector<int>{4,5,7,14,15},
	vector<int>{1,2,3,4,5},
	vector<int>{3,4,5,9,13}

};

class AlgorithmHelper
{
public:
	// 생성자: 알고리즘 반복횟수 입력
	AlgorithmHelper()
	{
		cin >> count;
	}

	void operator()(void)
	{
		if (count != 0)
		{
			DoAlgorithm();
			count--;
			operator()();
		}
	}

	virtual ~AlgorithmHelper() = default;

protected:
	// 입력을 도와주는 부분
	template<typename Head, typename ... Tails>
	void Read(Head& head, Tails& ... tails)
	{
		cin >> head;
		Read(tails...);
	}

	template<typename T>
	void Read(T& input)
	{
		cin >> input;
	}

	// 출력을 도와주는 부분
	template<typename Head, typename ... Tails>
	void Print(const Head& head, Tails& ... tails)
	{
		cout << head << ' ';
		Print(tails...);
	}

	template<typename T>
	void Print(const T& output)
	{
		cout << output << endl;
	}

private:
	int count;	// 입력 횟수

	void DoAlgorithm(void)
	{
		Input();
		Result();
	}

	// 실제 알고리즘을 작성할 순수 가상 함수
	virtual void Input(void) = 0;
	virtual void Result(void) = 0;
};

class SolveClockSync final : public AlgorithmHelper
{
private:
	vector<int> times = vector<int>(16, 0);

	void Input(void) override
	{
		for (auto i = 0; i < times.size(); ++i)
		{
			Read(times[i]);
		}
	}

	void Result(void) override
	{
		ClockSync test1(times);
		if (test1.DoAlgorithm())
			cout << test1.GetResult() << endl;
		else
			cout << -1 << endl;
	}
};

void TestCases(void)
{
	ClockSync test1(vector<int>{12, 6, 6, 6, 6, 6, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12});
	if (test1.DoAlgorithm())
		cout << test1.GetResult() << endl;
	else
		cout << -1 << endl;
	ClockSync test2(vector<int>{12, 9, 3, 12, 6, 6, 9, 3, 12, 9, 12, 9, 12, 12, 6, 6});
	if (test2.DoAlgorithm())
		cout << test2.GetResult() << endl;
	else
		cout << -1 << endl;
}

void Run(void)
{
	SolveClockSync solver;
	solver();
}

int main()
{
	//TestCases();
	Run();
	return 0;
}
