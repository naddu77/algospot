// DiamondPath.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DiamondPath
{
public:
	DiamondPath() = delete;
	DiamondPath(const int N, const vector<int>& diamond)
		: N(N), diamond(diamond)
	{

	}

	~DiamondPath() = default;

	int DoAlgorithm(void) const
	{
		vector<int> results(diamond.size());
		results[0] = diamond[0];

		auto start = 0;
		for (auto i = 0; i < N - 1; ++i)
		{
			const auto n = i + 1;
			start += n;
			for (auto j = start; j < start + n + 1; ++j)
			{
				if (j == start)	// 시작
					results[j] = diamond[j] + results[j - n];
				else if (j == start + n)	// 끝
					results[j] = diamond[j] + results[j - n - 1];
				else
					results[j] = results[j - n] > results[j - n - 1] ? diamond[j] + results[j - n] : diamond[j] + results[j - n - 1];
			}
		}

		for (auto i = N; i < 2 * N - 1; ++i)
		{
			const auto n = 2 * N - i - 1;
			start += n + 1;
			for (auto j = start; j < start + n; ++j)
				results[j] = results[j - n - 1] > results[j - n] ? diamond[j] + results[j - n - 1] : diamond[j] + results[j - n];
		}

		return results.back();
	}

private:
	const int N;
	const vector<int> diamond;
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
		Init();
		Input();
		Result();
	}

	// 실제 알고리즘을 작성할 가상 함수
	virtual void Init(void)
	{

	}

	virtual void Input(void) = 0;
	virtual void Result(void) = 0;
};

class SolveDiamondPath final : public AlgorithmHelper
{
private:
	int N;
	vector<int> diamond;

	void Init(void) override
	{
		diamond.clear();
	}

	void Input(void) override
	{
		Read(N);
		const auto element_count = Sum(N);
		diamond.resize(element_count);
		for (auto i = 0; i < element_count; ++i)
			Read(diamond[i]);
	}

	void Result(void) override
	{
		Print(DiamondPath(N, diamond).DoAlgorithm());
	}

	int Sum(const int n, const int acc = 0) const
	{
		return n == 1 ? acc + N : Sum(n - 1, acc + 2 * (n - 1));
	}
};

void TestCases(void)
{
	cout << DiamondPath(5, vector<int>{6,1,2,6,7,4,9,4,1,7,6,7,5,9,4,4,4,3,2,1,2,3,6,1,7}).DoAlgorithm() << endl;
	cout << DiamondPath(5, vector<int>{39,43,16,74,94,24,25,76,98,62,79,58,71,67,98,43,55,27,44,10,96,56,73,31,95}).DoAlgorithm() << endl;
}

void Run(void)
{
	SolveDiamondPath solver;
	solver();
}

int main()
{
	//TestCases();
	Run();
	return 0;
}
