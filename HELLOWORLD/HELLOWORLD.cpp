// HELLOWORLD.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
	std::vector<std::string> names;
	int count;
	std::cin >> count;
	for (auto i = 0; i < count; ++i)
	{
		std::string name;
		std::cin >> name;
		names.push_back(std::move(name));
	}

	std::for_each(names.begin(), names.end(), [](const std::string name) { std::cout << "Hello, " << name << "!" << std::endl; });

	return 0;
}
