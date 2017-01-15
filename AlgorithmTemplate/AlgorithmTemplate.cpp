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
	// ������: �˰��� �ݺ�Ƚ�� �Է�
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
	// �Է��� �����ִ� �κ�
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

	// ����� �����ִ� �κ�
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
	int count;	// �Է� Ƚ��

	void DoAlgorithm(void)
	{
		Init();
		Input();
		Result();
	}

	// ���� �˰����� �ۼ��� ���� ���� �Լ�
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
		// �ʱ�ȭ �ڵ�
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
