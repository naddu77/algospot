// MAXSUM.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

class MaxSum
{
public:
	MaxSum(const list<int>& sequence)
		: sequence(sequence)
	{

	}
	~MaxSum() = default;

	class AlgorithmFunctor
	{
	public:
		int result = 0;
		int sum_of_partial_sequence = 0;
		void operator()(int n) { result = max(result, sum_of_partial_sequence = sum_of_partial_sequence > -n ? sum_of_partial_sequence + n : 0); }
	};

	int DoAlgorithm(void)
	{
		return for_each(begin(sequence), end(sequence), AlgorithmFunctor()).result;
	}

private:
	list<int> sequence;
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

class SolveMaxSum final : public AlgorithmHelper
{
private:
	list<int> sequence;

	void Init(void) override
	{
		// �ʱ�ȭ �ڵ�
		sequence.clear();
	}

	void Input(void) override
	{
		int N;
		Read(N);
		for (auto i = 0; i < N; ++i)
		{
			int number;
			Read(number);
			sequence.push_back(number);
		}
	}

	void Result(void) override
	{
		Print(MaxSum(sequence).DoAlgorithm());
	}
};

void TestCases(void)
{
	cout << MaxSum({ 1, 2, 3, 4 }).DoAlgorithm() << endl;
	cout << MaxSum({ -1, 0, 1 }).DoAlgorithm() << endl;
}

void Run(void)
{
	SolveMaxSum solver;
	solver();
}

int main()
{
	//TestCases();
	Run();
	return 0;
}
