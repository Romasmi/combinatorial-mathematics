#include "stdafx.h"
#include <boost/timer.hpp>
using namespace std;

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

			reverse(pi.begin() + leftElementPosition + 1, pi.end());
		}
	}

	printf("Time: %.2f \n", time.elapsed());
    return 0;
}

