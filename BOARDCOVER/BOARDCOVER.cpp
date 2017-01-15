// BOARDCOVER.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <array>
#include <map>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

class Coins
{
public:
	Coins() = delete;
	Coins(const int H, const int W, const vector<vector<char>>& board)
		: H(H), W(W), board(board)
	{
	}
	~Coins() = default;

	int DoAlgorithm(void)
	{
		auto putable_position = GetPutablePosition();
		if (putable_position.first == -1)
			return 1;

		int result = 0;

		for (int i = 0; i < 4; ++i)
			if (CanPutShape(i, putable_position))
			{
				PutShape(i, putable_position);
				result += DoAlgorithm();
				ClearShape(i, putable_position);
			}

		return result;
	}

private:
	const int H;
	const int W;
	vector<vector<char>> board;

	// (h, w)
	const array<array<pair<int, int>, 3>, 4> shapes = array<array<pair<int, int>, 3>, 4>{
		array<pair<int, int>, 3>{ make_pair(0, 0), make_pair(1, 0), make_pair(1, 1) },
			array<pair<int, int>, 3>{ make_pair(0, 0), make_pair(0, 1), make_pair(1, 0) },
			array<pair<int, int>, 3>{ make_pair(0, 0), make_pair(0, 1), make_pair(1, 1) },
			array<pair<int, int>, 3>{ make_pair(0, 0), make_pair(1, 0), make_pair(1, -1)}
	};

	pair<int, int> GetPutablePosition(void) const
	{
		for (auto h = 0; h < H; ++h)
			for (auto w = 0; w < W; ++w)
				if (board[h][w] == '.')
					return make_pair(h, w);
		return make_pair(-1, -1);
	}

	bool CanPutShape(int shape_index, pair<int, int> center) const
	{
		return all_of(shapes[shape_index].begin(), shapes[shape_index].end(), [&](pair<int, int> point) {
			return IsInBoard(center.first + point.first, center.second + point.second) ?
				board[center.first + point.first][center.second + point.second] == '.' : false;
		});
	}

	bool IsInBoard(const int h, const int w) const
	{
		return h >= 0 && h < H && w >= 0 && w < W;
	}

	void PutShape(int shape_index, pair<int, int> center)
	{
		for (auto point : shapes[shape_index])
			board[center.first + point.first][center.second + point.second] = '#';
	}

	void ClearShape(int shape_index, pair<int, int> center)
	{
		for (auto point : shapes[shape_index])
			board[center.first + point.first][center.second + point.second] = '.';
	}

	void ShowBoard(void) const
	{
		cout << "-= Show Board =-" << endl;
		for (auto h : board)
		{
			for (auto w : h)
			{
				cout << w;
			}
			cout << endl;
		}
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
	int H;
	int W;
	vector<vector<char>> board;

	void Init(void) override
	{
		board.clear();
	}

	void Input(void) override
	{
		Read(H, W);
		for (auto h = 0; h < H; ++h)
		{
			string input;
			vector<char> temp;
			Read(input);
			for (auto c : input)
				temp.emplace_back(c);
			board.emplace_back(temp);
		}
	}

	void Result(void) override
	{
		Print(Coins(H, W, board).DoAlgorithm());
	}
};

void TestCases(void)
{
	// 0
	vector<vector<char>> test1 = {
		{ '#','.','.','.','.','.','#' },
		{ '#','.','.','.','.','.','#' },
		{ '#','#','.','.','.','#','#' },
	};

	//cout << BoardCover(3, 7, test1).DoAlgorithm() << endl;
	assert(Coins(3, 7, test1).DoAlgorithm() == 0);

	// 2
	vector<vector<char>> test2 = {
		{ '#','.','.','.','.','.','#' },
		{ '#','.','.','.','.','.','#' },
		{ '#','#','.','.','#','#','#' },
	};
	//cout << BoardCover(3, 7, test2).DoAlgorithm() << endl;
	assert(Coins(3, 7, test2).DoAlgorithm() == 2);

	// 1514
	vector<vector<char>> test3 = {
		{ '#','#','#','#','#','#','#','#','#','#' },
		{ '#','.','.','.','.','.','.','.','.','#' },
		{ '#','.','.','.','.','.','.','.','.','#' },
		{ '#','.','.','.','.','.','.','.','.','#' },
		{ '#','.','.','.','.','.','.','.','.','#' },
		{ '#','.','.','.','.','.','.','.','.','#' },
		{ '#','.','.','.','.','.','.','.','.','#' },
		{ '#','#','#','#','#','#','#','#','#','#' },
	};
	//cout << BoardCover(8, 10, test3).DoAlgorithm() << endl;
	assert(Coins(8, 10, test3).DoAlgorithm() == 1514);
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