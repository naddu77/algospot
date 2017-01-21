// BOOKTHIEF_example.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include <algorithm> // max
#include <iostream>
#include <vector>

// Strategy
// --------
// Convert this Bounded Knapsack to 0-1 Knapsack
// then apply 0-1 Knapsack algorithm

typedef std::vector<int> IntVec;

void
convert01(int *v, int *c, int *k, int N,
	IntVec &v01, IntVec &c01, int &N01)
{
	N01 = 0;
	for (int i = 0; i < N; ++i) {
		int b = 0; // [0..k[i]]
		int j = 1; // [1..k[i]-b]
		while (b != k[i]) {
			if (b + j > k[i])
				j = k[i] - b;
			c01.push_back(j * c[i]);
			v01.push_back(j * v[i]);
			b += j;
			j *= 2;
			++N01;
		}
	}
}

int
bookthief01(IntVec v, IntVec c, int N, int V)
{
	// DP array -- C[i][j]
	int **C = new int *[N + 1];
	for (int i = 0; i < N + 1; ++i)
		C[i] = new int[V + 1];

	// Init 0'th row and 0'th col with 0.
	// Max cost is 0 if the thief do not take book at all
	// or thief can carry only 0 volume. (very weak person).
	for (int i = 0; i <= N; ++i) {
		C[i][0] = 0;
	}
	for (int j = 0; j <= V; ++j) {
		C[0][j] = 0;
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= V; ++j) {
			if (j >= v[i - 1]) {
				C[i][j] = std::max(c[i - 1] + C[i - 1][j - v[i - 1]], C[i - 1][j]);
			}
			else {
				C[i][j] = C[i - 1][j];
			}
		}
	}

	int max_stolen = C[N][V];
	for (int i = 0; i < N + 1; ++i) {
		delete[] C[i];
	}
	delete[] C;

	return max_stolen;

}

int
main(void)
{
	int t;
	std::cin >> t;
	while (--t >= 0) {
		// Number of book types, Volume of bag
		int N, V;
		std::cin >> N >> V;

		// Volume, Cost, Count of books
		int *v = new int[N];
		int *c = new int[N];
		int *k = new int[N];
		for (int i = 0; i < N; ++i)
			std::cin >> v[i] >> c[i] >> k[i];

		// Convert to 0-1 Knapsack
		IntVec v01;
		IntVec c01;
		int N01;
		convert01(v, c, k, N, v01, c01, N01);
		delete[] v;
		delete[] c;
		delete[] k;
		// DEBUG
		// for (int i = 0; i < N01; ++i) {
		//     std::cout << v01[i] << " " << c01[i] << std::endl;
		// }

		std::cout << bookthief01(v01, c01, N01, V) << std::endl;
	}
	return 0;
}