#include "pch.h"
using namespace std;

template <class T>
bool Between(const T item, const T min, const T max)
{
	return item >= min && item <= max;
}

template <class T>
T Sum(vector<T>& v)
{
	T sum = 0;
	for (const T& item : v)
		sum += item;
	return sum;
}

using Set = vector<size_t>;

Set GetPlacementBySet(const Set& set, const size_t base, const size_t endOffset = 1)
{
	vector<size_t> placement;
	for (size_t i = 0; i < set.size() - endOffset; ++i)
	{
		if (Between<size_t>(set[i], 1, base))
		{
			placement.push_back(set[i]);
		}
	}
	return placement;
}

void Print(const vector<size_t>& v, const size_t offset = 0, const size_t endOffset = 0, const string dilimiter = "")
{
	if (v.size() > 0)
	{
		copy(v.begin() + offset, v.end() - endOffset, ostream_iterator<int>(cout, ""));
		cout << '\n';
	}
}

void PrintComposition(const vector<size_t>& v)
{
	if (v.size() > 0)
	{
		for (size_t i = 0; i < v.size() - 1; ++i)
		{
			cout << v[i] << " + ";
		}
		cout << v.back() << '\n';
	}
}

bool SetItemExist(const vector<Set>& v, const Set set)
{
	for (Set item : v)
	{
		if (item == set)
		{
			return true;
		}
	}
	return false;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid count  of arguments";
		return 1;
	}
	const size_t n = stoul(argv[1]);
	if (n < 2)
	{
		cout << "Invalid Number";
		return 1;
	}

	Set set(n + 1);
	vector<Set> compositions;
	fill(set.begin(), set.end(), 0);
	while (set[n] != 1)
	{
		Set composition = GetPlacementBySet(set, n, 1);
		if (Sum<size_t>(composition) == n && !SetItemExist(compositions, composition))
		{
			compositions.push_back(composition);
			PrintComposition(composition);
		}
		size_t i = 0;
		while (set[i] == n - 1)
		{
			set[i] = 0;
			++i;
		}
		++set[i];
	}
}
