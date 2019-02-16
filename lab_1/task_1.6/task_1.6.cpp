#include "pch.h"
using namespace std;

void PrintBySet(const vector<int> &set, size_t endOffset)
{
	bool printed = false;
	for (size_t i = 0; i < set.size() - endOffset; ++i)
	{
		if (set[i] == 1)
		{
			printed = true;
			cout << i + 1;
		}
	}
	if (printed)
	{
		cout << '\n';
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid count  of arguments";
		return 1;
	}

	const size_t n = stoul(argv[1]);


	boost::timer time;

	vector<int> set(n + 1);
	fill(set.begin(), set.end(), 0);
	while (set[n] != 1)
	{
		//PrintBySet(set, 1);
		size_t i = 0;
		while (set[i] == 1)
		{
			set[i] = 0;
			++i;
		}
		set[i] = 1;
	}

	printf("Time: %.3f \n", time.elapsed());
}
