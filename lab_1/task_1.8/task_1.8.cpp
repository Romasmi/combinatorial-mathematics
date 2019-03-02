#include "pch.h"
using namespace std;
const int FIRST_LINE_PARAMS_COUNT = 3;
const int LINE_PARAMS_COUNT = 2;

struct Cargo
{
	size_t weight;
	size_t cost;
};

using Backpack = vector<Cargo>;
using LineItems = vector<size_t>;

struct Params
{
	size_t size;
	size_t maxWeight;
	size_t minCost;
	Backpack backpack;
};

LineItems Explode(const string& line, const char separator = ' ')
{
	LineItems items;
	string item;
	for (size_t i = 0; i < line.size(); ++i)
	{
		if (line[i] != separator)
		{
			item += line[i];
		}
		else
		{
			items.push_back(stoull(item));
			item.clear();
		}
	}
	items.push_back(stoull(item));
	return items;
}

void Print(const vector<int>& v, const size_t endOffset = 1)
{
	copy(v.begin(), v.end() - endOffset, ostream_iterator<size_t>(cout, " "));
	cout << '\n';
}

bool ParseStream(Params& params, istream& input)
{
	string line;
	LineItems items;
	if (!getline(input, line))
	{
		return false;
	}

	items = Explode(line);
	if (items.size() != FIRST_LINE_PARAMS_COUNT)
	{
		return false;
	}
	params.size = items[0];
	params.maxWeight = items[1];
	params.minCost = items[2];

	while (getline(input, line))
	{
		items = Explode(line);
		if (items.size() != LINE_PARAMS_COUNT)
		{
			return false;
		}
		params.backpack.push_back({ items[0], items[1] });
	}

	return params.backpack.size() == params.size;
}

Backpack GetCombination(const vector<int>& set, const Backpack& backpack)
{
	vector<Cargo> combination;
	for (size_t i = 0; i < backpack.size(); ++i)
	{
		if (set[i] == 1)
		{
			combination.push_back(backpack[i]);
		}
	}
	return combination;
}

size_t GetTotalWeight(const Backpack& backpack)
{
	return accumulate(backpack.begin(), backpack.end(), 0,
		[](const size_t sum, const Cargo &item) {
			return sum + item.weight;
		});
}

size_t GetTotalCost(const Backpack& backpack)
{
	return accumulate(backpack.begin(), backpack.end(), 0,
		[](const size_t sum, const Cargo& item) {
			return sum + item.cost;
		});
}

void PrintBestCombination(const Params& params)
{
	vector<int> set(params.size + 1);
	fill(set.begin(), set.end(), 0);
	Backpack bestCombitation;
	while (set[params.size + 1] != 1)
	{
		Backpack combination = GetCombination(set, params.backpack);
		const size_t totalWeight = GetTotalWeight(combination);
		const size_t totalCost = GetTotalCost(combination);
		if (totalCost >= params.minCost &&
			totalWeight <= params.maxWeight)
		{
			cout << totalWeight << '\n';
			Print(set);
			return;
		}

		size_t i = 0;
		while (set[i] == 1)
		{
			set[i] = 0;
			++i;
		}
		set[i] = 1;
	}
	
	cout << "Combination is not found\n";
}

int main()
{
	Params params;
	try
	{
		if (!ParseStream(params, cin))
		{
			return 1;
		}
	}
	catch (const exception& e)
	{
		cout << e.what() << '\n';
		return 1;
	}

	PrintBestCombination(params);
}
