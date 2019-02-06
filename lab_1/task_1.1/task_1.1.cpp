#include "stdafx.h"
#include <boost/timer.hpp>
using namespace std;

void PrintArray(const vector<size_t>& array, const size_t end = 0, const size_t start = 0)
{
	for (size_t i = start; i < end; ++i)
	{
		cout << array[i];
	}
	cout << '\n';
}

int main(const size_t argc, const char** argv)
{
	if (argc < 2)
	{
		return 1;
	}
	const size_t SIZE = atoi(argv[1]);
	size_t arraySize = SIZE + 2;

	boost::timer time;
	time.restart();

	printf("Time: %.2f \n", time.elapsed());
	return 0;
}