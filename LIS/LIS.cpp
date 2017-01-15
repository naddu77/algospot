// LIS.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class LIS
{
public:
	LIS() = delete;
	LIS(const vector<int>& sequence)
		: sequence(sequence), cache(sequence.size(), -1)
	{

	}
	~LIS() = default;

	int AlgorithmSub(int start)
	{
		int& subsequence_size = cache[start];
		if (subsequence_size != -1)
			return subsequence_size;

		subsequence_size = 1;

		for (int i = start + 1; i < sequence.size(); ++i)
			if (sequence[start] < sequence[i])
				subsequence_size = max(subsequence_size, AlgorithmSub(i) + 1);

		return subsequence_size;
	}

	int DoAlgorithm(void)
	{
		int subsequence_size = 0;
		for (int i = 0; i < sequence.size(); ++i)
			subsequence_size = max(subsequence_size, AlgorithmSub(i));
			
		return subsequence_size;
	}
private:
	const vector<int> sequence;
	vector<int> cache;
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

	// 실제 알고리즘을 작성할 순수 가상 함수
	virtual void Init(void)
	{

	}

	virtual void Input(void) = 0;
	virtual void Result(void) = 0;
};

class SolveLIS final : public AlgorithmHelper
{
private:
	vector<int> sequence;
	void Init(void) override
	{
		// 초기화 코드
		sequence.clear();
	}

	void Input(void) override
	{
		int N;
		Read(N);
		sequence.resize(N);
		for (auto& i : sequence)
			Read(i);
	}

	void Result(void) override
	{
		Print(LIS(sequence).DoAlgorithm());
	}
};

void TestCases(void)
{
	cout << LIS(vector<int>{1, 2, 3, 4}).DoAlgorithm() << endl;				// 4
	cout << LIS(vector<int>{5, 4, 3, 2, 1, 6, 7, 8}).DoAlgorithm() << endl;	// 4
	cout << LIS(vector<int>{5, 6, 7, 8, 1, 2, 3, 4}).DoAlgorithm() << endl;	// 4
	cout << LIS(vector<int>{1, 1, 1}).DoAlgorithm() << endl;		// 1
	cout << LIS(vector<int>{9, 1, 2, 3, 4}).DoAlgorithm() << endl;	// 4
	cout << LIS(vector<int>{2, 5, 6, 1, 2}).DoAlgorithm() << endl;	// 3
	cout << LIS(vector<int>{1, 3, 2, 4}).DoAlgorithm() << endl;		// 3
	cout << LIS(vector<int>{100}).DoAlgorithm() << endl;			// 1
	cout << LIS(vector<int>{100, 1, 101}).DoAlgorithm() << endl;	// 2
	cout << LIS(vector<int>{1, 5, 2, 3}).DoAlgorithm() << endl;		// 3
}

void Run(void)
{
	SolveLIS solver;
	solver();
}

int main()
{
	TestCases();
	//Run();
	return 0;
}
