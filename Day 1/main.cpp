#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int CalibrationNumber(const string& str, bool useWords = false)
{
	auto cStr = str.c_str();
	auto length = str.size();

	int firstDigit = 0;
	int lastDigit  = 0;

	int firstIndex = -1;
	int lastIndex  = -1;

	for (int i = 0; i < length; i++)
	{
		if (cStr[i] >= '0' && cStr[i] <= '9')
		{
			firstDigit = cStr[i] - '0';
			firstIndex = i;
			break;
		}
	}

	for (int i = length - 1; i >= 0; i--)
	{
		if (cStr[i] >= '0' && cStr[i] <= '9')
		{
			lastDigit = cStr[i] - '0';
			lastIndex = i;
			break;
		}
	}

	if (useWords)
	{

		static string wordsList[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
		auto crtDigit = 1;
		for (const auto& word : wordsList)
		{
			const int fi = str.find(word);
			const int li = str.rfind(word);

			if ((firstIndex == -1 || fi < firstIndex) && fi != string::npos)
			{
				firstIndex = fi;
				firstDigit = crtDigit;
			}

			if ((lastIndex == -1 || li > lastIndex) && li != string::npos)
			{
				lastIndex = li;
				lastDigit = crtDigit;
			}

			crtDigit++;
		}
	}
	return firstDigit * 10 + lastDigit;
}

int main()
{
	ifstream fin("input.txt");
	string currentString;

	int sum  = 0;
	int sum2 = 0;

	while (fin >> currentString)
	{
		sum  += CalibrationNumber(currentString);
		sum2 += CalibrationNumber(currentString, true);
	}

	cout << sum << endl;
	cout << sum2 << endl;

	fin.close();

	return 0;
}