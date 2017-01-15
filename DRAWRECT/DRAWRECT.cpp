// DRAWRECT.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

typedef struct
{
	int x;
	int y;
} POINT;

int main()
{
	int count;
	cin >> count;
	for (auto i = 0; i < count; ++i)
	{
		POINT point[3];
		for (auto j = 0; j < 3; ++j)
			cin >> point[j].x >> point[j].y;

		POINT output;
		if (point[0].x == point[1].x)
			output.x = point[2].x;
		else if (point[0].x == point[2].x)
			output.x = point[1].x;
		else
			output.x = point[0].x;

		if (point[0].y == point[1].y)
			output.y = point[2].y;
		else if (point[0].y == point[2].y)
			output.y = point[1].y;
		else
			output.y = point[0].y;

		cout << output.x << " " << output.y << endl;
	}
    return 0;
}

