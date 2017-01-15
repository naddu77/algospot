// WEEKLYCALENDAR.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <assert.h>

using namespace std;

class WeeklyCalendar
{
public:
	WeeklyCalendar() = delete;

	WeeklyCalendar(const int month, const int day, const string& day_of_the_week)
		: month(month - 1), day(day), not_refined_day(day - table_of_day_of_the_week.at(day_of_the_week))
	{
		weekly_calendar = MakeWeeklyCalendar();
	}

	~WeeklyCalendar() = default;

	const string& GetWeeklyCalendar(void) const
	{
		return weekly_calendar;
	}

private:
	string weekly_calendar;
	static const unordered_map<string, int> table_of_day_of_the_week;
	static const int day_table[];
	const int not_refined_day;
	const int month;
	const int day;
	static const int one_week = 7;

	string MakeWeeklyCalendar(const string& output = "", int i = one_week)
	{
		const int temp = not_refined_day + one_week - i;
		return i == 0 ? output : MakeWeeklyCalendar(
			output + to_string(
				temp < 1 ?
				day_table[(11 + month) % 12] + temp :
				(temp > day_table[month] ? temp - day_table[month] : temp)
			) + " ", i - 1);
	}
};

const unordered_map<string, int> WeeklyCalendar::table_of_day_of_the_week = {
	make_pair("Sunday", 0),
	make_pair("Monday", 1),
	make_pair("Tuesday", 2),
	make_pair("Wednesday", 3),
	make_pair("Thursday", 4),
	make_pair("Friday", 5),
	make_pair("Saturday", 6),
};

const int WeeklyCalendar::day_table[] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
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

class SolveWeeklyCalendar final : public AlgorithmHelper
{
private:
	int month;
	int day;
	string day_of_the_week;

	void Input(void) override
	{
		Read(month, day, day_of_the_week);
	}

	void Result(void) override
	{
		Print(WeeklyCalendar(month, day, day_of_the_week).GetWeeklyCalendar());
	}
};

void TestCases(void)
{
	WeeklyCalendar wc_arr[] = {
		WeeklyCalendar(7, 27, "Saturday"),	// 7월(달 바뀜 없음)
		WeeklyCalendar(7, 27, "Sunday"),	// 7월에서 8월
		WeeklyCalendar(7, 28, "Sunday"),	// 7월에서 8월
		WeeklyCalendar(7, 28, "Monday"),	// 7월에서 8월
		WeeklyCalendar(7, 29, "Tuesday"),	// 7월에서 8월
		WeeklyCalendar(7, 4, "Saturday"),	// 7월에서 6월
		WeeklyCalendar(1, 1, "Saturday"),	// 1월에서 12월
		WeeklyCalendar(1, 3, "Saturday"),	// 1월에서 12월
		WeeklyCalendar(3, 1, "Friday"),		// 3월에서 2월
		WeeklyCalendar(9, 30, "Wednesday"),	// 9월에서 10월
		WeeklyCalendar(12, 30, "Thursday"),	// 12월에서 1월
		WeeklyCalendar(2, 26, "Monday"),	// 2월에서 3월
		WeeklyCalendar(2, 3, "Saturday"),	// 2월에서 1월
		WeeklyCalendar(8, 2, "Saturday"),	// 8월에서 7월
		WeeklyCalendar(7, 27, "Monday"),	// 7월에서 8월
		WeeklyCalendar(5, 15, "Wednesday"),	// 달 바뀜 없음
		WeeklyCalendar(11, 30, "Wednesday"),	// 11월에서 12월
		WeeklyCalendar(11, 2, "Wednesday"),	// 11월에서 10월
	};

	string expected_string[] = {
		"21 22 23 24 25 26 27 ",
		"27 28 29 30 31 1 2 ",
		"28 29 30 31 1 2 3 ",
		"27 28 29 30 31 1 2 ",
		"27 28 29 30 31 1 2 ",
		"28 29 30 1 2 3 4 ",
		"26 27 28 29 30 31 1 ",
		"28 29 30 31 1 2 3 ",
		"24 25 26 27 28 1 2 ",
		"27 28 29 30 1 2 3 ",
		"26 27 28 29 30 31 1 ",
		"25 26 27 28 1 2 3 ",
		"28 29 30 31 1 2 3 ",
		"27 28 29 30 31 1 2 ",
		"26 27 28 29 30 31 1 ",
		"12 13 14 15 16 17 18 ",
		"27 28 29 30 1 2 3 ",
		"30 31 1 2 3 4 5 "
	};

	for (auto i = 0; i < sizeof(wc_arr) / sizeof(wc_arr[0]); ++i)
		assert(wc_arr[i].GetWeeklyCalendar() == expected_string[i]);
}

void Run(void)
{
	SolveWeeklyCalendar solver;
	solver();
}

int main()
{
	TestCases();
	Run();
    return 0;
}

