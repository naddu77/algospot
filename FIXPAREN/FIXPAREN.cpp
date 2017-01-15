// FIXPAREN.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <array>

using namespace std;

class Coins
{
public:
	Coins() = delete;
	Coins(string sequence_of_transcribed_parentheses, string priority_order_of_parentheses_types)
		: sequence_of_transcribed_parentheses(sequence_of_transcribed_parentheses),
		priority_order_of_parentheses_types(priority_order_of_parentheses_types)
	{
		for (auto i = 0; i < priority_order_of_parentheses_types.size(); ++i)
		{
			switch (priority_order_of_parentheses_types[i])
			{
			case '(':
				priorty_table[i][0] = '(';
				priorty_table[i][1] = ')';
				break;
			case '{':
				priorty_table[i][0] = '{';
				priorty_table[i][1] = '}';
				break;
			case '[':
				priorty_table[i][0] = '[';
				priorty_table[i][1] = ']';
				break;
			case '<':
				priorty_table[i][0] = '<';
				priorty_table[i][1] = '>';
				break;
			}
		}
	}
	~Coins() = default;

	string DoAlgorithm(void)
	{
		string result = sequence_of_transcribed_parentheses;
		for (auto i = 0 ; i < result.size(); ++i)
		{
			if (IsStart(result[i]))
				s.push(i);
			else if (IsOk(result[i]))
				s.pop();
			else
			{
				for (auto j = 0; j < sizeof(priorty_table) / sizeof(priorty_table[0]); ++j)
				{
					if (result[s.top()] == priorty_table[j][0] || result[i] == priorty_table[j][1])
					{
						result[s.top()] = priorty_table[j][0];
						result[i] = priorty_table[j][1];
						break;
					}
				}
				s.pop();
			}
		}

		return result;
	}

private:
	string sequence_of_transcribed_parentheses;
	string priority_order_of_parentheses_types;
	unordered_map<char, char> table = {
		{')', '('},
		{'}', '{'},
		{']', '['},
		{'>', '<'}
	};
	char priorty_table[4][2];
	stack<unsigned int> s;
	const array<char, 4> start_brakets = { '(', '{', '[', '<' };

	bool IsStart(const char c) const
	{
		return any_of(start_brakets.begin(), start_brakets.end(), [c](char data) { return c == data; });
		//return c == '(' || c == '{' || c == '[' || c == '<';
	}

	bool IsOk(const char c) const
	{
		return sequence_of_transcribed_parentheses[s.top()] == table.at(c);
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

class SolveCoins final : public AlgorithmHelper
{
private:
	string sequence_of_transcribed_parentheses;
	string priority_order_of_parentheses_types;

	void Input(void) override
	{
		Read(sequence_of_transcribed_parentheses, priority_order_of_parentheses_types);
	}

	void Result(void) override
	{
		Print(Coins(sequence_of_transcribed_parentheses, priority_order_of_parentheses_types).DoAlgorithm());
	}
};

void TestCases(void)
{
	cout << Coins("(}", "{(<[").DoAlgorithm() << endl;
	cout << Coins("()([)>", "<({[").DoAlgorithm() << endl;
	cout << Coins("()([)]", "[{<(").DoAlgorithm() << endl;
	cout << Coins("([}{])", "{(<[").DoAlgorithm() << endl;
	cout << Coins("[<{({)})}]", "<{([").DoAlgorithm() << endl;
}

void Run(void)
{
	SolveCoins solver;
	solver();
}

int main()
{
	//TestCases();
	Run();
    return 0;
}

