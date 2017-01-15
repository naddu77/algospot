// ROUTING.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <queue>

using namespace std;
using NoiseTable = vector<tuple<int, int, double>>;

class Routing
{
public:
	Routing() = delete;
	Routing(const int& V, const NoiseTable noise_table)
		: v(V), adj(10001)
	{
		for (const auto& noise_info : noise_table)
			adj[get<0>(noise_info)].emplace_back(make_pair(get<1>(noise_info), get<2>(noise_info)));
	}
	~Routing() = default;

	auto DoAlgorithm(void) const
	{
		vector<double> dist(v, numeric_limits<double>::max());
		dist[0] = 0.0;
		priority_queue<pair<double, int>> pq;
		pq.emplace(make_pair(0.0, 0));
		while (!pq.empty())
		{
			auto cost = -pq.top().first;
			auto here = pq.top().second;
			pq.pop();

			if (dist[here] < cost)
				continue;

			for (auto i = 0u; i < adj[here].size(); ++i)
			{
				auto there = adj[here][i].first;
				auto nextDist = cost + log10(adj[here][i].second);

				if (dist[there] > nextDist)
				{
					dist[there] = nextDist;
					pq.emplace(make_pair(-nextDist, there));
				}
			}
		}

		return pow(10, dist[v - 1]);
	}

private:
	int v;
	vector<vector<pair<int, double>>> adj;
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

class SolveRouting final : public AlgorithmHelper
{
private:
	int number_of_computer;
	NoiseTable noise_table;

	void Init(void) override
	{
		noise_table.clear();
	}

	void Input(void) override
	{
		int number_of_noise_info;
		
		Read(number_of_computer, number_of_noise_info);
		for (auto i = 0; i < number_of_noise_info; ++i)
		{
			int a, b;
			double c;
			Read(a, b, c);
			noise_table.emplace_back(make_tuple(a, b, c));
		}
	}

	void Result(void) override
	{
		Print(Routing(number_of_computer, noise_table).DoAlgorithm());
	}
};

void TestCases(void)
{
	cout <<  Routing(7,
	NoiseTable{
		make_tuple( 0, 1, 1.3 ),
		make_tuple( 0, 2, 1.1 ),
		make_tuple( 0, 3, 1.24 ),
		make_tuple( 3, 4, 1.17 ),
		make_tuple( 3, 5, 1.24 ),
		make_tuple( 3, 1, 2 ),
		make_tuple( 1, 2, 1.31 ),
		make_tuple( 1, 2, 1.26 ),
		make_tuple( 1, 4, 1.11 ),
		make_tuple( 1, 5, 1.37 ),
		make_tuple( 5, 4, 1.24 ),
		make_tuple( 4, 6, 1.77 ),
		make_tuple( 5, 6, 1.11 ),
		make_tuple( 2, 6, 1.2 ),
	}).DoAlgorithm() << endl;

	cout << Routing(4,
		NoiseTable{
			make_tuple(0, 1, 2.0),
			make_tuple(0, 3, 12.0),
			make_tuple(1, 2, 4.0),
			make_tuple(3, 2, 3.0)
	}).DoAlgorithm() << endl;
}

void Run(void)
{
	SolveRouting solver;
	solver();
}

int main()
{
	cout.precision(10);
	cout << fixed;
	
	TestCases();
	//Run();

	return 0;
}
