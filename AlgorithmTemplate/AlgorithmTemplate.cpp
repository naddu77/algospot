// AlgorithmTemplate.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>

using namespace std;

class Coins
{
public:
	Coins() = delete;
	~Coins() = default;

private:
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
	void Print(const Head& head, Tails& ... tails) const
	{
		cout << head << ' ';
		Print(tails...);
	}

	template<typename T>
	void Print(const T& output) const
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

class SolveCoins final : public AlgorithmHelper
{
private:
	void Init(void) override
	{
		// 초기화 코드
	}

	void Input(void) override
	{
		//Read(input1, input2);
	}

	void Result(void) override
	{
		//Print(AlgorithmClassName(input1, input2).DoAlgorithm());
	}
};

void TestCases(void)
{
	//cout << AlgorithmClassName("(}", "{(<[").DoAlgorithm() << endl;
}

void Run(void)
{
	//AlgorithmClassName solver;
	//solver();
}

int main()
{
	TestCases();
	//Run();
	return 0;
}
