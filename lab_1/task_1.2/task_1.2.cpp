#include "stdafx.h"
#include <boost/timer.hpp>
using namespace std;

void PrintArray(vector<size_t>& array, const size_t end = 0, const size_t start = 0)
{
	for (size_t i = start; i <= end; ++i)
	{
		cout << array[i];
	}
	cout << '\n';
}

void ReverseArray(vector<size_t>& array, const size_t end = 0, const size_t start = 0)
{
	for (size_t i = start, j = end; i < j; i++, j--)
	{
		swap(array[i], array[j]);
	}
}

int main(const int argc, const char** argv)
{
	if (argc < 2)
	{
		return 1;
	}
	const size_t SIZE = atoi(argv[1]);

	vector<size_t> pi(SIZE + 2);

	for (size_t i = 1; i <= SIZE; ++i)
	{
		pi[i] = i;
	}

	boost::timer time;
	time.restart();
	bool elementToMoveFound = true;
	while (elementToMoveFound)
	{
		elementToMoveFound = false;
		size_t leftElementPosition;
		for (size_t i = SIZE - 1; i >= 1; --i)
		{
			if (pi[i] < pi[i + 1])
			{
				elementToMoveFound = true;
				leftElementPosition = i;
				break;
			}
		}

		if (elementToMoveFound)
		{
			size_t minimalRightElement = SIZE + 1;
			size_t rightElementPosition;
			for (size_t i = leftElementPosition + 1; i <= SIZE; ++i)
			{
				if (pi[leftElementPosition] < pi[i] && pi[i] < minimalRightElement)
				{
					minimalRightElement = pi[i];
					rightElementPosition = i;
				}
			}

			swap(pi[leftElementPosition], pi[rightElementPosition]);

			ReverseArray(pi, SIZE, leftElementPosition + 1);
		}
	}

	printf("Time: %.2f \n", time.elapsed());
    return 0;
}

