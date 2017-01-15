// NQueen.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Coins
{
public:
	Coins() = delete;
	Coins(const int n)
		: n(n)
	{
		
	}

	~Coins() = default;

	int DoSlowAlgorithm(int result = 0, const int y = 0)
	{
		if (y >= n)
			return result + 1;

		for (auto i = 0; i < n; ++i)
		{
			if (IsValid(i, y))
			{
				queens.push_back(i);
				result = DoSlowAlgorithm(result, y + 1);
				queens.pop_back();
			}
		}

		return result;
	}

	int AlgorithmSub(int result = 0, const int y = 0)
	{
		if (y >= n)
			return result + 1;
		int count = y == 0 ? n >> 1 : n;
		for (auto i = 0; i < count; ++i)
		{
			if (IsValid(i, y))
			{
				queens.push_back(i);
				result = AlgorithmSub(result, y + 1);
				queens.pop_back();
			}
		}

		return result;
	}

	int DoAlgorithm(void)
	{
		int result = AlgorithmSub() << 1;

		if (IsOdd())
		{
			const int mid = n >> 1;
			if (IsValid(mid, 0))
			{
				queens.push_back(mid);
				result = AlgorithmSub(result, 1);
				queens.pop_back();
			}
		}

		return result;
	}

private:
	const int n;
	vector<int> queens;

	bool IsValid(const int x, const int y)
	{
		for (int i = 0; i < queens.size(); ++i)
		{
			const int diff = y - i;
			if (x == queens[i] || x == queens[i] + diff || x == queens[i] - diff)
				return false;
		}

		return true;
	}

	bool IsOdd(void) const
	{
		return n % 2 == 1;
	}
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

class SolveNQueen final : public AlgorithmHelper
{
private:
	int n;

	void Input(void) override
	{
		Read(n);
	}

	void Result(void) override
	{
		Print(Coins(n).DoAlgorithm());
	}
};

void TestCases(void)
{
	for(auto i = 1 ; i <= 12; ++i)
		cout << Coins(i).DoAlgorithm() << endl;
}

void Run(void)
{
	SolveNQueen solver;
	solver();
}

int main()
{
	//TestCases();
	Run();
	return 0;
}
