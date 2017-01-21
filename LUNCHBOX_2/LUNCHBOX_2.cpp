// LUNCHBOX_2.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class LunchBox
{
public:
	LunchBox() = delete;
	LunchBox(const vector<pair<int, int>>& lunchbox_information)
		: lunchbox_information(lunchbox_information)
	{
		sort(begin(this->lunchbox_information), end(this->lunchbox_information), greater<pair<int, int>>());
	}
	~LunchBox() = default;

	class AlgorithmFunctor
	{
	public:
		int result = 0;
		int begin_eat = 0;
		void operator()(const pair<int, int>& info) { result = max(result, (begin_eat += info.second) + info.first); }
	};

	int DoAlgorithm(void) const
	{
		return for_each(begin(lunchbox_information), end(lunchbox_information), AlgorithmFunctor()).result;
	}

private:
	vector<pair<int, int>> lunchbox_information;	// (E, M)
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

class SolveLunchBox final : public AlgorithmHelper
{
private:
	vector<pair<int, int>> lunchbox_information;

	void Init(void) override
	{
		// �ʱ�ȭ �ڵ�
		lunchbox_information.clear();
	}

	void Input(void) override
	{
		int number_of_lunchbox;
		Read(number_of_lunchbox);
		vector<int> M(number_of_lunchbox);
		vector<int> E(number_of_lunchbox);
		for (auto i = 0; i < number_of_lunchbox; ++i)
			Read(M[i]);
		for (auto i = 0; i < number_of_lunchbox; ++i)
			Read(E[i]);
		for (auto i = 0; i < number_of_lunchbox; ++i)
			lunchbox_information.emplace_back(make_pair(E[i], M[i]));

	}

	void Result(void) override
	{
		Print(LunchBox(lunchbox_information).DoAlgorithm());
	}
};

void TestCases(void)
{
	cout << LunchBox({ { 2,2 },{ 2,2 },{ 2,2 } }).DoAlgorithm() << endl;
	cout << LunchBox({ { 1,1 },{ 2,2 },{ 1,3 } }).DoAlgorithm() << endl;
}

void Run(void)
{
	SolveLunchBox solver;
	solver();
}

int main()
{
	//TestCases();
	Run();
	return 0;
}