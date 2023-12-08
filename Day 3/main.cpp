#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>

using namespace std;

bool TouchingSign(const vector<vector<char>>& schematic, const int rows, const int columns, const int row, const int col, set<pair<int, int>>& neighbors)
{
	static int dRow[] = { -1, 0, 1, 0, -1, -1, 1, 1 };
	static int dCol[] = { 0, -1, 0, 1, -1, 1, -1, 1 };

	bool neighbor = false;

	for (int i = 0; i < 8; i++)
	{
		const auto newRow = row + dRow[i];
		const auto newCol = col + dCol[i];

		if (newRow < 0 || newRow >= rows ||
			newCol < 0 || newCol >= columns)
			continue;

		const char chr = schematic[newRow][newCol];

		if (chr != '.' && (chr < '0' || chr > '9'))
		{
			auto rowCol = make_pair(newRow, newCol);

			if (neighbors.find(rowCol) == neighbors.end())
				neighbors.insert(rowCol);

			neighbor = true;
		}
	}

	return neighbor;
}

int main()
{
	ifstream fin("input.txt");
	vector<vector<char>> schematic;
	string line;

	while (fin >> line)
	{
		vector<char> tmp;
		for (const auto& c : line)
			tmp.push_back(c);
		schematic.push_back(tmp);
	}

	fin.close();

	const int rows    = schematic.size();
	const int columns = schematic[0].size();

	int result1 = 0, result2 = 0;

	map<pair<int, int>, vector<int>> symbolsNeighbors;

	for (int row = 0; row < rows; row++)
	{
		int                 parsedNumber = 0;
		bool                touchingSign = false;
		set<pair<int, int>> numberNeighbors;

		for (int col = 0; col < columns; col++)
		{
			const auto currentChr = schematic[row][col];
			const auto isDigit = currentChr >= '0' && currentChr <= '9';

			if (isDigit)
			{
				parsedNumber *= 10;
				parsedNumber += currentChr - '0';
				touchingSign = touchingSign || TouchingSign(schematic, rows, columns, row, col, numberNeighbors);
			}

			if (!isDigit || col == columns - 1)
			{
				if (touchingSign)
					result1 += parsedNumber;

				for (auto& signPos : numberNeighbors)
				{
					if (symbolsNeighbors.find(signPos) == symbolsNeighbors.end())
						symbolsNeighbors[signPos] = vector<int>();
					symbolsNeighbors[signPos].push_back(parsedNumber);
				}

				parsedNumber = 0;
				touchingSign = false;
				numberNeighbors.clear();
			}
		}
	}

	for (const auto& rowColVec : symbolsNeighbors)
	{
		const auto& rowCol = rowColVec.first;
		const auto& vec = rowColVec.second;

		if (schematic[rowCol.first][rowCol.second] != '*')
			continue;

		if (vec.size() != 2)
			continue;

		result2 += vec[0] * vec[1];
	}

	cout << result1 << endl;
	cout << result2 << endl;

	return 0;
}