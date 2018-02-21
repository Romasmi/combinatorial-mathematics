#include "stdafx.h"
#include <boost/timer.hpp>
using namespace std;

void PrintPermutation(vector<int>& pi)
{
	size_t SIZE = pi.size() - 1;
	bool elementToMoveFound = true;
	while (elementToMoveFound)
	{
		//copy(pi.begin() + 1, pi.end(), ostream_iterator<int>(cout, " "));
		//cout << "\n";

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
			size_t minimalRightElement = pi[leftElementPosition + 1] + 1;
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
}

bool PrintAccomodations(const unsigned int k, const unsigned int n)
{
	if (k > n)
	{
		cout << "K must be less or equil to N" << endl;
		return false;
	}

	vector<int> combination(k + 1);

	combination[0] = -1;
	for (unsigned int i = 1; i <= k; ++i)
	{
		combination[i] = i;
	}

	unsigned int j = 1;
	while (j != 0)
	{
		/*copy(combination.begin(), combination.end(), ostream_iterator<int>(cout, " "));
		cout << "\n";*/

		vector<int> pi = combination;
		PrintPermutation(pi);

		j = k;
		while (combination[j] == n - k + j)
		{
			--j;
		}
		++combination[j];
	
		for (unsigned int i = j + 1; i <= k; ++i)
		{
			combination[i] = combination[i - 1] + 1;
		}
	}

	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid  parameter count" << endl;
		return 1;
	}

	unsigned int k;
	unsigned int n;
	try
	{
		k = stoi(argv[1]);
		n = stoi(argv[2]);
	}
	catch (exception &e)
	{
		cout << e.what() << endl;
		return 1;
	}

	if (k > n)
	{
		cout << "K must be less or equil to N" << endl;
		return 1;
	}

	boost::timer time;
	time.restart();

	PrintAccomodations(k, n);

	printf("Time: %.2f \n", time.elapsed());
	return 0;
}

