// BRACKETS2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Brackets2
{
public:
	Brackets2() = delete;
	Brackets2(const string& str)
		: str(str)
	{

	}
	~Brackets2() = default;

	bool IsValidStructureOfBrackets(void)
	{
		return all_of(str.begin(), str.end(), [&](const char c)
		{
			if (IsStart(c))
				s.push(c);
			else if (IsOk(c))
				s.pop();
			else
				return false;
			return true;
		}) && s.empty();
	}

private:
	string str;
	stack<char> s;
	const unordered_map<char, char> table = { {')', '('}, {'}', '{'}, {']', '['} };

	bool IsStart(const char c) const
	{
		return c == '(' || c == '{' || c == '[';
	}

	bool IsOk(const char c) const
	{
		return !s.empty() && s.top() == table.at(c);
	}
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
	int count;	// �Է� Ƚ��

	void DoAlgorithm(void)
	{
		Input();
		Result();
	}

	// ���� �˰����� �ۼ��� ���� ���� �Լ�
	virtual void Input(void) = 0;
	virtual void Result(void) = 0;
};

class SolveBrackets2 final : public AlgorithmHelper
{
private:
	string str;

	void Input(void) override
	{
		Read(str);
	}

	void Result(void) override
	{
		if (Brackets2(str).IsValidStructureOfBrackets())
			Print("YES");
		else
			Print("NO");
	}
};

void TestCases(void)
{
	cout << Brackets2("()()").IsValidStructureOfBrackets() << endl;
	cout << Brackets2("({[}])").IsValidStructureOfBrackets() << endl;
	cout << Brackets2("({}[(){}])").IsValidStructureOfBrackets() << endl;
	cout << Brackets2("()()()(){{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{)))))))))))(((((((((()()()(()()())()(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((").IsValidStructureOfBrackets() << endl;
	cout << Brackets2("]").IsValidStructureOfBrackets() << endl;
}

void Run(void)
{
	SolveBrackets2 solver;
	solver();
}

int main()
{
	Run();
	//TestCases();

    return 0;
}

