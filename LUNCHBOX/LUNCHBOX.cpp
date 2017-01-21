// LUNCHBOX.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

// 시간초과

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

	}
	~LunchBox() = default;

	int DoAlgorithm(void)
	{
		sort(begin(lunchbox_information), end(lunchbox_information), greater<pair<int, int>>());
		auto time = 0u;
		auto lunchbox_index = 0u;
		while (true)
		{
			if(all_of(begin(lunchbox_information), end(lunchbox_information), [](const pair<int, int>& e) {
				return e.first < 0;
			}))
				break;

			if (lunchbox_index < lunchbox_information.size())
			{
				lunchbox_information[lunchbox_index].second--;
				if (lunchbox_information[lunchbox_index].second == 0)
					lunchbox_index++;
			}

			for (auto i = 0u; i < lunchbox_index; ++i)
				lunchbox_information[i].first--;

			time++;
		}

		return time;
	}

private:
	vector<pair<int, int>> lunchbox_information;	// (E, M)
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

class SolveLunchBox final : public AlgorithmHelper
{
private:
	vector<pair<int, int>> lunchbox_information;

	void Init(void) override
	{
		// 초기화 코드
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
