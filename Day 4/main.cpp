#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>

using namespace std;

int ProcessLine(const string& line, bool& any)
{
	auto usefulLine = line.substr(line.find(":") + 1, line.size());

	auto chosenNumberLine = usefulLine.substr(0, usefulLine.find("|"));
	auto goodNumbersLine = usefulLine.substr(usefulLine.find("|") + 1, usefulLine.size());

	stringstream ss1;
	ss1 << chosenNumberLine;
	stringstream ss2;
	ss2 << goodNumbersLine;

	unordered_set<int> goodNumbers;
	int number;
	while (ss2 >> number)
		goodNumbers.insert(number);

	int pow = -1;
	while (ss1 >> number)
		if (goodNumbers.find(number) != goodNumbers.end())
			pow++;

	if (pow >= 0)
		any = true;

	return pow >= 0 ? pow : 0;
}

void AddFromToIndex(vector<int>& vec, const int from, const int to, const int value)
{
	for (int i = from; i < to; i++)
	{
		if (vec.size() <= i)
			vec.push_back(value);
		else
			vec[i] += value;
	}
}

int main()
{
	ifstream fin("input.txt");

	string line;
	vector<int> numberCount;

	int result1 = 0, result2 = 0;
	int index = 0;
	while (getline(fin, line))
	{
		while (numberCount.size() <= index)
			numberCount.push_back(0);
		numberCount[index]++;

		bool any = false;
		int matches = ProcessLine(line, any);
		if (any)
		{
			result1 += 1 << matches;
			matches++;
		}
		AddFromToIndex(numberCount, index + 1, index + 1 + matches, numberCount[index]);

		index++;
	}

	for (auto number : numberCount)
		result2 += number;

	cout << result1 << endl;
	cout << result2 << endl;

	fin.close();

	return 0;
}