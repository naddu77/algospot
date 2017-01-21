// BOOKTHIEF.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <functional>

using namespace std;

class BookThief
{
public:
	BookThief() = delete;
	BookThief(const int V, const vector<tuple<int, int, int>>& book_information)
		: V(V)
	{
		for (auto i = 0; i < book_information.size(); ++i)
		{
			auto b = 0;
			auto j = 1;
			int v, c, k;
			tie(v, c, k) = book_information[i];

			while (b != k)
			{
				if (b + j > k)
					j = k - b;
				cv.emplace_back(make_pair(j * c, j * v));
				b += j;
				j *= 2;
			}
		}
	}
	~BookThief() = default;

	int DoAlgorithm(void)
	{
		vector<vector<int>> dp_table(cv.size() + 1);
		for (auto& i : dp_table)
			i.resize(V + 1, 0);

		for (auto i = 1; i <= cv.size(); ++i)
		{
			for (auto j = 1; j <= V; ++j)
			{
				if (j >= cv[i - 1].second)
					dp_table[i][j] = max(cv[i - 1].first + dp_table[i - 1][j - cv[i - 1].second], dp_table[i - 1][j]);
				else
					dp_table[i][j] = dp_table[i - 1][j];
			}
		}

		return dp_table[cv.size()][V];
	}

private:
	int V;
	vector<pair<int, int>> cv;
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

class SolveBookThief final : public AlgorithmHelper
{
private:
	int V;
	vector<tuple<int, int, int>> book_information;	// (v, c, k)

	void Init(void) override
	{
		// 초기화 코드
		book_information.clear();
	}

	void Input(void) override
	{
		int books;
		Read(books, V);
		for (auto i = 0; i < books; ++i)
		{
			int v, c, k;
			Read(v, c, k);
			book_information.emplace_back(make_tuple(v, c, k));
		}
	}

	void Result(void) override
	{
		Print(BookThief(V, book_information).DoAlgorithm());
	}
};

void TestCases(void)
{
	cout << BookThief(100, { {50,100,2},{40,100,1},{2,1,50} }).DoAlgorithm() << endl;
}

void Run(void)
{
	SolveBookThief solver;
	solver();
}

int main()
{
	//TestCases();
	Run();
	return 0;
}
