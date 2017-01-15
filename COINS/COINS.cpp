// COINS.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <array>

using namespace std;

class Coins
{
public:
	Coins() = delete;
	Coins(const int exchange_money, const vector<int>& coins)
		: exchange_money(exchange_money), coins(coins)
	{
	}
	~Coins() = default;

	long long DoAlgorithm(void) const
	{
		array<long long, 5001> dp_table{ 1ll, };
		for (auto coin : coins)
		{
			cout << "coin: " << coin << endl;
			for (auto i = coin; i <= exchange_money; ++i)
			{
				dp_table[i] += dp_table[i - coin] % 1000000007;
				if (dp_table[i] > 0)
					cout << "[" << i << "]: " << dp_table[i] << endl;
			}
		}

		return dp_table[exchange_money] % 1000000007;
	}

private:
	const int exchange_money;
	const vector<int> coins;
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

class SolveCoins final : public AlgorithmHelper
{
private:
	int exchange_money;
	vector<int> coins;

	void Init(void) override
	{
		coins.clear();
	}

	void Input(void) override
	{
		int number_of_types_of_coin;
		Read(exchange_money, number_of_types_of_coin);
		coins.resize(number_of_types_of_coin);
		for (auto i = 0; i < number_of_types_of_coin; ++i)
			Read(coins[i]);
	}

	void Result(void) override
	{
		Print(Coins(exchange_money, coins).DoAlgorithm());
	}
};

void TestCases(void)
{
	//cout << Coins(110, vector<int>{10, 50, 100, 500}).DoAlgorithm() << endl;
	cout << Coins(850, vector<int>{10, 50, 100, 500}).DoAlgorithm() << endl;
	//cout << Coins(3600, vector<int>{100, 300, 500, 900, 2000}).DoAlgorithm() << endl;
	//cout << Coins(1278, vector<int>{1, 2, 4, 8, 16, 32, 64, 128}).DoAlgorithm() << endl;
}

void Run(void)
{
	SolveCoins solver;
	solver();
}

int main()
{
	TestCases();
	//Run();
	return 0;
}
