#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

typedef unsigned long long ull;

struct RGB
{
	int red   = 0;
	int green = 0;
	int blue  = 0;
};

struct LineInfo
{
	int index = 0;
	RGB maxRGB {};
};

RGB ProcessSet(const string& set)
{
	RGB result;

	stringstream ss;

	ss << set;

	int    number;
	string channel;

	while (ss >> number >> channel)
	{
		if (channel.rfind("red") == 0)
			result.red += number;
		else if (channel.rfind("green") == 0)
			result.green += number;
		else if (channel.rfind("blue") == 0)
			result.blue += number;
		else
			cout << "What the hell?" << endl;
	}

	return result;
}

LineInfo ProcessLine(const string& str)
{
	LineInfo result;

	auto lineInfo = str.substr(0, str.find(":"));

	stringstream ss;
	ss << lineInfo;
	string junk;
	
	ss >> junk >> result.index;

	auto usefulLine = str.substr(str.find(":") + 1, str.size());

	auto gotSets = true;

	while (gotSets) 
	{
		string set = "";
		if (usefulLine.find(";") != string::npos)
		{
			set = usefulLine.substr(0, usefulLine.find(";"));
			usefulLine = usefulLine.substr(usefulLine.find(";") + 1, usefulLine.size());
		}
		else
		{
			set = usefulLine;
			gotSets = false;
		}

		auto rgb = ProcessSet(set);

		result.maxRGB.red   = max(result.maxRGB.red,   rgb.red);
		result.maxRGB.green = max(result.maxRGB.green, rgb.green);
		result.maxRGB.blue  = max(result.maxRGB.blue,  rgb.blue);
	}

	return result;
}

int main()
{
	ifstream fin("input.txt");

	string crtLine;

	RGB targetRgb;
	targetRgb.red   = 12;
	targetRgb.green = 13;
	targetRgb.blue  = 14;

	int result1 = 0;

	ull totalPower = 0;

	while (getline(fin, crtLine))
	{
		ull power = 0;

		auto lineInfo = ProcessLine(crtLine);

		if (lineInfo.maxRGB.red <= targetRgb.red &&
			lineInfo.maxRGB.green <= targetRgb.green &&
			lineInfo.maxRGB.blue <= targetRgb.blue)
			result1 += lineInfo.index;

		power = (ull)lineInfo.maxRGB.red * (ull)lineInfo.maxRGB.green * (ull)lineInfo.maxRGB.blue;
		totalPower += power;
	}

	fin.close();

	cout << result1 << endl;
	cout << totalPower << endl;

	return 0;
}