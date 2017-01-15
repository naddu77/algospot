// HAMMINGCODE.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main()
{
	int count;
	cin >> count;
	while (count--)
	{
		bitset<7> input;
		cin >> input;

		bitset<3> syndrome;

		syndrome[0] = input[6] ^ input[4] ^ input[2] ^ input[0];
		syndrome[1] = input[5] ^ input[4] ^ input[1] ^ input[0];
		syndrome[2] = input[3] ^ input[2] ^ input[1] ^ input[0];
		
		unsigned long error_position = syndrome.to_ulong();
		if(error_position)
			input[7 - error_position] = ~input[7 - error_position];

		bitset<4> decoded_message;
		decoded_message[3] = input[4];
		decoded_message[2] = input[2];
		decoded_message[1] = input[1];
		decoded_message[0] = input[0];

		cout << decoded_message << endl;
	}
    return 0;
}

