// SHISENSHO.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <tuple>
#include <random>
#include <memory>

using namespace std;

class ShiSenSho
{
public:
	ShiSenSho(const int h, const int w)
		: H(h), W(w)
	{
		board = new char*[H];
		for (auto i = 0; i < H; ++i)
		{
			board[i] = new char[W + 1];
		}
	}

	~ShiSenSho()
	{
		for (auto i = 0; i < H; ++i)
		{
			delete[] board[i];
		}
		delete[] board;
	}

	bool SetTile(const int h, const int w, const char the_tile)
	{
		bool is_valid = IsValid(h, w);
		if(is_valid)
			board[h][w] = the_tile;
		return is_valid;

	}

	void ShowBoard(void) const
	{
		cout << "-= Show Board =-" << endl;
		for (auto h = 0; h < H; ++h)
		{
			for (auto w = 0; w < W; ++w)
			{
				cout << board[h][w];
			}
			cout << endl;
		}
	}

	int DoAlgorithm(void)
	{
		unsigned int result = 0;
		for (auto h = 1; h < H - 1; ++h)
		{
			for (auto w = 1; w < W - 1; ++w)
			{
				if (board[h][w] != '.')
				{
					char the_tile = board[h][w];
					board[h][w] = '=';	// 중복 탐색을 막기 위한 꼼수(쌍이니까 두 번 찾게 됨)

					FindSingleMove(result, the_tile, h, w);

					// 보드 원상복구
					RestoreBoard(the_tile);
				}
			}
		}

		return result;
	}

private:
	int H;
	int W;
	char** board;

	enum class Direction
	{
		ORIGIN,
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	bool IsValid(int h, int w) const
	{
		return h >= 0 && h < H && w >= 0 && w < W;
	}

	void FindSingleMove(unsigned int& result, char the_tile, int h, int w, Direction direction = Direction::ORIGIN, unsigned int line_segments = 0)
	{
		if (!IsValid(h, w))
			return;

		if (board[h][w] == 0)	// 이미 찾은 tile
			return;

		if (line_segments < 4)
		{
			if (the_tile != '=' || direction == Direction::ORIGIN)
			{
				if (board[h][w] == '.' || direction == Direction::ORIGIN)
				{
					switch (direction)
					{
					case Direction::ORIGIN:
						FindSingleMove(result, the_tile, h, w - 1, Direction::LEFT, line_segments + 1);
						FindSingleMove(result, the_tile, h - 1, w, Direction::UP, line_segments + 1);
						FindSingleMove(result, the_tile, h, w + 1, Direction::RIGHT, line_segments + 1);
						FindSingleMove(result, the_tile, h + 1, w, Direction::DOWN, line_segments + 1);
						break;
					case Direction::LEFT:
						FindSingleMove(result, the_tile, h, w - 1, Direction::LEFT, line_segments);
						FindSingleMove(result, the_tile, h - 1, w, Direction::UP, line_segments + 1);
						FindSingleMove(result, the_tile, h + 1, w, Direction::DOWN, line_segments + 1);
						break;
					case Direction::UP:
						FindSingleMove(result, the_tile, h, w - 1, Direction::LEFT, line_segments + 1);
						FindSingleMove(result, the_tile, h - 1, w, Direction::UP, line_segments);
						FindSingleMove(result, the_tile, h, w + 1, Direction::RIGHT, line_segments + 1);
						break;
					case Direction::RIGHT:
						FindSingleMove(result, the_tile, h - 1, w, Direction::UP, line_segments + 1);
						FindSingleMove(result, the_tile, h, w + 1, Direction::RIGHT, line_segments);
						FindSingleMove(result, the_tile, h + 1, w, Direction::DOWN, line_segments + 1);
						break;
					case Direction::DOWN:
						FindSingleMove(result, the_tile, h, w - 1, Direction::LEFT, line_segments + 1);
						FindSingleMove(result, the_tile, h, w + 1, Direction::RIGHT, line_segments + 1);
						FindSingleMove(result, the_tile, h + 1, w, Direction::DOWN, line_segments);
						break;
					default:
						break;
					}
				}
				else if (the_tile == board[h][w])
				{
					board[h][w] = 0;	// 중복 탐색을 막기 위한 꼼수(다양한 경로가 있을 수 있음)
					result++;
				}
			}
		}
	}

	void RestoreBoard(const char the_tile)
	{
		for (auto h = 1; h < H - 1; ++h)
		{
			for (auto w = 1; w < W - 1; ++w)
			{
				if (board[h][w] == 0)
					board[h][w] = the_tile;
			}
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
	int H;
	int W;
	typedef shared_ptr<ShiSenSho> ShiSenShoPtr;
	ShiSenShoPtr sss;

	void Input(void) override
	{
		Read(H, W);
		sss.reset(new ShiSenSho(H, W));
		for (auto h = 0; h < H; ++h)
		{
			string str;
			Read(str);
			for (auto w = 0; w < W; ++w)
				sss->SetTile(h, w, str[w]);
		}
	}

	void Result(void) override
	{
		Print(sss->DoAlgorithm());
	}
};

void TestCase1(void)
{
	ShiSenSho sss(4, 5);

	sss.SetTile(0, 0, '.'), sss.SetTile(0, 1, '.'), sss.SetTile(0, 2, '.'), sss.SetTile(0, 3, '.'), sss.SetTile(0, 4, '.');
	sss.SetTile(1, 0, '.'), sss.SetTile(1, 1, 'A'), sss.SetTile(1, 2, '.'), sss.SetTile(1, 3, 'A'), sss.SetTile(1, 4, '.');
	sss.SetTile(2, 0, '.'), sss.SetTile(2, 1, '.'), sss.SetTile(2, 2, '.'), sss.SetTile(2, 3, 'A'), sss.SetTile(2, 4, '.');
	sss.SetTile(3, 0, '.'), sss.SetTile(3, 1, '.'), sss.SetTile(3, 2, '.'), sss.SetTile(3, 3, '.'), sss.SetTile(3, 4, '.');

	cout << sss.DoAlgorithm() << endl;
}

void TestCase2(void)
{
	ShiSenSho sss(4, 7);

	sss.SetTile(0, 0, '.'), sss.SetTile(0, 1, '.'), sss.SetTile(0, 2, '.'), sss.SetTile(0, 3, '.'), sss.SetTile(0, 4, '.'), sss.SetTile(0, 5, '.'), sss.SetTile(0, 6, '.');
	sss.SetTile(1, 0, '.'), sss.SetTile(1, 1, 'A'), sss.SetTile(1, 2, '.'), sss.SetTile(1, 3, 'X'), sss.SetTile(1, 4, '.'), sss.SetTile(1, 5, 'A'), sss.SetTile(1, 6, '.');
	sss.SetTile(2, 0, '.'), sss.SetTile(2, 1, 'A'), sss.SetTile(2, 2, '.'), sss.SetTile(2, 3, 'Y'), sss.SetTile(2, 4, '.'), sss.SetTile(2, 5, 'A'), sss.SetTile(2, 6, '.');
	sss.SetTile(3, 0, '.'), sss.SetTile(3, 1, '.'), sss.SetTile(3, 2, '.'), sss.SetTile(3, 3, '.'), sss.SetTile(3, 4, '.'), sss.SetTile(3, 5, '.'), sss.SetTile(3, 6, '.');

	cout << sss.DoAlgorithm() << endl;
}

void TestCase3(void)
{
	ShiSenSho sss(10, 10);

	sss.SetTile(0, 0, '.'), sss.SetTile(0, 1, '.'), sss.SetTile(0, 2, '.'), sss.SetTile(0, 3, '.'), sss.SetTile(0, 4, '.'), sss.SetTile(0, 5, '.'), sss.SetTile(0, 6, '.'), sss.SetTile(0, 7, '.'), sss.SetTile(0, 8, '.'), sss.SetTile(0, 9, '.');
	sss.SetTile(1, 0, '.'), sss.SetTile(1, 1, '.'), sss.SetTile(1, 2, '.'), sss.SetTile(1, 3, '.'), sss.SetTile(1, 4, '.'), sss.SetTile(1, 5, '.'), sss.SetTile(1, 6, '.'), sss.SetTile(1, 7, '.'), sss.SetTile(1, 8, '.'), sss.SetTile(1, 9, '.');
	sss.SetTile(2, 0, '.'), sss.SetTile(2, 1, '.'), sss.SetTile(2, 2, '.'), sss.SetTile(2, 3, '.'), sss.SetTile(2, 4, '.'), sss.SetTile(2, 5, '.'), sss.SetTile(2, 6, '.'), sss.SetTile(2, 7, 'c'), sss.SetTile(2, 8, '.'), sss.SetTile(2, 9, '.');
	sss.SetTile(3, 0, '.'), sss.SetTile(3, 1, '.'), sss.SetTile(3, 2, '.'), sss.SetTile(3, 3, '.'), sss.SetTile(3, 4, '.'), sss.SetTile(3, 5, '.'), sss.SetTile(3, 6, '.'), sss.SetTile(3, 7, 'A'), sss.SetTile(3, 8, '.'), sss.SetTile(3, 9, '.');
	sss.SetTile(4, 0, '.'), sss.SetTile(4, 1, '.'), sss.SetTile(4, 2, 'a'), sss.SetTile(4, 3, '.'), sss.SetTile(4, 4, '.'), sss.SetTile(4, 5, '.'), sss.SetTile(4, 6, '.'), sss.SetTile(4, 7, 'a'), sss.SetTile(4, 8, '.'), sss.SetTile(4, 9, '.');
	sss.SetTile(5, 0, '.'), sss.SetTile(5, 1, '.'), sss.SetTile(5, 2, 'A'), sss.SetTile(5, 3, '.'), sss.SetTile(5, 4, '.'), sss.SetTile(5, 5, '.'), sss.SetTile(5, 6, '.'), sss.SetTile(5, 7, 'A'), sss.SetTile(5, 8, '.'), sss.SetTile(5, 9, '.');
	sss.SetTile(6, 0, '.'), sss.SetTile(6, 1, '.'), sss.SetTile(6, 2, '.'), sss.SetTile(6, 3, '.'), sss.SetTile(6, 4, '.'), sss.SetTile(6, 5, '.'), sss.SetTile(6, 6, '.'), sss.SetTile(6, 7, 'C'), sss.SetTile(6, 8, '.'), sss.SetTile(6, 9, '.');
	sss.SetTile(7, 0, '.'), sss.SetTile(7, 1, '.'), sss.SetTile(7, 2, '.'), sss.SetTile(7, 3, '.'), sss.SetTile(7, 4, '.'), sss.SetTile(7, 5, '.'), sss.SetTile(7, 6, '.'), sss.SetTile(7, 7, 'C'), sss.SetTile(7, 8, '.'), sss.SetTile(7, 9, '.');
	sss.SetTile(8, 0, '.'), sss.SetTile(8, 1, '.'), sss.SetTile(8, 2, '.'), sss.SetTile(8, 3, '.'), sss.SetTile(8, 4, '.'), sss.SetTile(8, 5, '.'), sss.SetTile(8, 6, '.'), sss.SetTile(8, 7, '.'), sss.SetTile(8, 8, '.'), sss.SetTile(8, 9, '.');
	sss.SetTile(9, 0, '.'), sss.SetTile(9, 1, '.'), sss.SetTile(9, 2, '.'), sss.SetTile(9, 3, '.'), sss.SetTile(9, 4, '.'), sss.SetTile(9, 5, '.'), sss.SetTile(9, 6, '.'), sss.SetTile(9, 7, '.'), sss.SetTile(9, 8, '.'), sss.SetTile(9, 9, '.');

	cout << sss.DoAlgorithm() << endl;
}

void TestCase4(void)
{
	ShiSenSho sss(4, 5);

	sss.SetTile(0, 0, '.'), sss.SetTile(0, 1, '.'), sss.SetTile(0, 2, '.'), sss.SetTile(0, 3, '.'), sss.SetTile(0, 4, '.');
	sss.SetTile(1, 0, '.'), sss.SetTile(1, 1, 'Q'), sss.SetTile(1, 2, 'W'), sss.SetTile(1, 3, '.'), sss.SetTile(1, 4, '.');
	sss.SetTile(2, 0, '.'), sss.SetTile(2, 1, 'A'), sss.SetTile(2, 2, 'A'), sss.SetTile(2, 3, 'R'), sss.SetTile(2, 4, '.');
	sss.SetTile(3, 0, '.'), sss.SetTile(3, 1, '.'), sss.SetTile(3, 2, '.'), sss.SetTile(3, 3, '.'), sss.SetTile(3, 4, '.');

	cout << sss.DoAlgorithm() << endl;
}

void TestCase5(void)
{
	ShiSenSho sss(3, 30);

	for (auto h = 0; h < 3; ++h)
		for(auto w = 0; w < 30; ++w)
			sss.SetTile(h, w, '.');

	sss.SetTile(1, 11, 'm');
	sss.SetTile(1, 19, 'Q');
	sss.SetTile(1, 21, 'P');
	sss.SetTile(1, 22, 'A');
	sss.SetTile(1, 23, 'c');
	sss.SetTile(1, 28, 'j');

	cout << sss.DoAlgorithm() << endl;
}

void TestCase6(void)
{
	ShiSenSho sss(8, 10);

	sss.SetTile(0, 0, '.'), sss.SetTile(0, 1, '.'), sss.SetTile(0, 2, '.'), sss.SetTile(0, 3, '.'), sss.SetTile(0, 4, '.'), sss.SetTile(0, 5, '.'), sss.SetTile(0, 6, '.'), sss.SetTile(0, 7, '.'), sss.SetTile(0, 8, '.'), sss.SetTile(0, 9, '.');
	sss.SetTile(1, 0, '.'), sss.SetTile(1, 1, 'A'), sss.SetTile(1, 2, '.'), sss.SetTile(1, 3, 'B'), sss.SetTile(1, 4, '.'), sss.SetTile(1, 5, 'C'), sss.SetTile(1, 6, '.'), sss.SetTile(1, 7, '.'), sss.SetTile(1, 8, '.'), sss.SetTile(1, 9, '.');
	sss.SetTile(2, 0, '.'), sss.SetTile(2, 1, '.'), sss.SetTile(2, 2, '.'), sss.SetTile(2, 3, '.'), sss.SetTile(2, 4, '.'), sss.SetTile(2, 5, 'G'), sss.SetTile(2, 6, 'D'), sss.SetTile(2, 7, '.'), sss.SetTile(2, 8, 'A'), sss.SetTile(2, 9, '.');
	sss.SetTile(3, 0, '.'), sss.SetTile(3, 1, '.'), sss.SetTile(3, 2, '.'), sss.SetTile(3, 3, '.'), sss.SetTile(3, 4, 'F'), sss.SetTile(3, 5, '.'), sss.SetTile(3, 6, '.'), sss.SetTile(3, 7, '.'), sss.SetTile(3, 8, 'G'), sss.SetTile(3, 9, '.');
	sss.SetTile(4, 0, '.'), sss.SetTile(4, 1, 'C'), sss.SetTile(4, 2, 'E'), sss.SetTile(4, 3, '.'), sss.SetTile(4, 4, '.'), sss.SetTile(4, 5, 'B'), sss.SetTile(4, 6, '.'), sss.SetTile(4, 7, '.'), sss.SetTile(4, 8, '.'), sss.SetTile(4, 9, '.');
	sss.SetTile(5, 0, '.'), sss.SetTile(5, 1, '.'), sss.SetTile(5, 2, '.'), sss.SetTile(5, 3, '.'), sss.SetTile(5, 4, '.'), sss.SetTile(5, 5, '.'), sss.SetTile(5, 6, 'E'), sss.SetTile(5, 7, '.'), sss.SetTile(5, 8, '.'), sss.SetTile(5, 9, '.');
	sss.SetTile(6, 0, '.'), sss.SetTile(6, 1, '.'), sss.SetTile(6, 2, 'G'), sss.SetTile(6, 3, '.'), sss.SetTile(6, 4, '.'), sss.SetTile(6, 5, '.'), sss.SetTile(6, 6, '.'), sss.SetTile(6, 7, '.'), sss.SetTile(6, 8, 'F'), sss.SetTile(6, 9, '.');
	sss.SetTile(7, 0, '.'), sss.SetTile(7, 1, '.'), sss.SetTile(7, 2, '.'), sss.SetTile(7, 3, '.'), sss.SetTile(7, 4, '.'), sss.SetTile(7, 5, '.'), sss.SetTile(7, 6, '.'), sss.SetTile(7, 7, '.'), sss.SetTile(7, 8, '.'), sss.SetTile(7, 9, '.');


	cout << sss.DoAlgorithm() << endl;
}

void TestCaseRandom(void)
{
	random_device rand_device;
	default_random_engine generator;
	uniform_int_distribution<int> distribution(3, 50);
	uniform_int_distribution<int> tile_distribution('A', 'z');
	uniform_int_distribution<int> point_distribution(0, 1);
	int H = distribution(rand_device);
	int W = distribution(rand_device);
	
	ShiSenSho sss(H, W);

	// 자동으로 판 만들기
	for(auto w = 0 ; w < W ; ++ w)
		sss.SetTile(0, w, '.');
	for (auto w = 0; w < W; ++w)
		sss.SetTile(H - 1, w, '.');
	for (auto h = 0; h < H; ++h)
		sss.SetTile(h, 0, '.');
	for (auto h = 0; h < H; ++h)
		sss.SetTile(h, W - 1, '.');

	for(auto h = 1 ; h < H - 1 ; ++h)
		for (auto w = 1; w < W - 1; ++w)
		{
			char the_tile = tile_distribution(rand_device);
			if (the_tile > 90 && the_tile < 97)
				sss.SetTile(h, w, '.');
			else if(point_distribution(rand_device) == 0)
				sss.SetTile(h, w, the_tile);
			else
				sss.SetTile(h, w, '.');
		}

	cout << sss.DoAlgorithm() << endl;
}



void TestCases(void)
{
	TestCase1();
	TestCase2();
	TestCase3();
	TestCase4();
	TestCase5();
	TestCase6();
	while (true)
		TestCaseRandom();
}

void Run(void)
{
	SolveCoins solver;
	solver();
}

int main()
{
	TestCase6();
	Run();
	//TestCases();
    return 0;
}

