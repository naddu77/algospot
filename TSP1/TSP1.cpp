// TSP1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

class Coins
{
public:
	Coins() = delete;
	Coins(const vector<vector<double>>& distance_table)
		: distance_table(distance_table)
	{

	}

	~Coins() = default;

	double DoAlgorithm(void)
	{
		vector<int> index;
		for (auto i = 0; i < distance_table.size(); ++i)
			index.push_back(i);

		vector<double> distances;
		do 
		{
			double distance = 0.0;
			for (auto i = 0; i < index.size() - 1; ++i)
				distance += distance_table[index[i]][index[i + 1]];
			distances.emplace_back(distance);
		} while (next_permutation(index.begin(), index.end()));

		return *min_element(distances.begin(), distances.end());
	}

private:
	vector<vector<double>> distance_table;
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
	int number_of_city;
	vector<vector<double>> distance_table;
	void Input(void) override
	{
		distance_table.clear();
		Read(number_of_city);
		for (auto i = 0; i < number_of_city; ++i)
		{
			vector<double> temp_vector;
			for (auto j = 0; j < number_of_city; ++j)
			{
				double temp;
				Read(temp);
				temp_vector.emplace_back(temp);
			}
			distance_table.emplace_back(temp_vector);
		}
	}

	void Result(void) override
	{
		Print(Coins(distance_table).DoAlgorithm());
	}
};

void TestCases(void)
{
	//cout << AlgorithmClassName("(}", "{(<[").DoAlgorithm() << endl;
	cout << Coins(vector<vector<double>>{
		{0.0000000000, 611.6157225201, 648.7500617289},
		{ 611.6157225201,  0.0000000000,  743.8557967501 },
		{ 648.7500617289,  743.8557967501,  0.0000000000 },
	}).DoAlgorithm() << endl;

	cout << Coins(vector<vector<double>>{
		{0.0000000000, 326.0008994586, 503.1066076077, 290.0250922998},
		{326.0008994586, 0.0000000000, 225.1785728436, 395.4019367384},
		{503.1066076077, 225.1785728436, 0.0000000000, 620.3945520632},
		{290.0250922998, 395.4019367384,  620.3945520632, 0.0000000000},
	}).DoAlgorithm() << endl;

	cout << Coins(vector<vector<double>>{
		{0.0000000000, 583.6148530169, 840.7827256437, 872.9038568553, 127.4630209093, 312.1081610732, 726.8224753099, 89.0380209726},
		{583.6148530169, 0.0000000000, 469.5209369387, 992.2041697391, 937.3466917022, 706.9851759388, 68.0494075958, 466.9476153641},
		{840.7827256437, 469.5209369387, 0.0000000000, 798.9871202963, 923.5693723539, 255.9277882129, 139.2735741750, 970.6744677251},
		{872.9038568553, 992.2041697391, 798.9871202963, 0.0000000000, 535.7531893699, 350.4435654499, 159.0177794728, 580.6143966413},
		{127.4630209093, 937.3466917022, 923.5693723539, 535.7531893699, 0.0000000000, 17.3375546082, 262.7304220864, 736.6005036685},
		{312.1081610732, 706.9851759388, 255.9277882129, 350.4435654499, 17.3375546082, 0.0000000000, 378.5676650603, 595.1593651414},
		{726.8224753099, 68.0494075958, 139.2735741750, 159.0177794728, 262.7304220864, 378.5676650603, 0.0000000000, 583.0571132633},
		{89.0380209726, 466.9476153641, 970.6744677251, 580.6143966413, 736.6005036685, 595.1593651414, 583.0571132633, 0.0000000000},
	}).DoAlgorithm() << endl;
}

void Run(void)
{
	SolveCoins solver;
	solver();
}

int main()
{
	cout.precision(10);
	cout << fixed;
	//TestCases();
	Run();
	return 0;
}
