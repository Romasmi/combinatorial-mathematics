#include "stdafx.h"
#include <boost/timer.hpp>
using namespace std;

void PrintArray(vector<size_t>& array, const size_t end = 0, const size_t start = 0)
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
	vector<size_t> pi(arraySize);
	vector<size_t> p(arraySize);
	vector<size_t> d(arraySize);

	for (size_t i = 1; i <= SIZE; ++i)
	{
		pi[i] = i;
		p[i] = i;
		d[i] = -1;
	}
	d[1] = 0;
	size_t m = SIZE + 1;
	pi[0] = m;
	pi[SIZE + 1] = m;

	boost::timer time;
	time.restart();
	while (m != 1)
	{
		m = SIZE;

		while (pi[p[m] + d[m]] > m)
		{
			d[m] *= -1;
			m = m - 1;
		}

		swap(pi[p[m]], pi[p[m] + d[m]]);
		swap(p[pi[p[m]]], p[m]);
	}

	printf("Time: %.2f \n", time.elapsed());
	return 0;
}