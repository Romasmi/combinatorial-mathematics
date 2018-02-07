#include "stdafx.h"
#include <ctime>
using namespace std;

void PrintArray(int* array, const int end = 0, const int start = 0)
{
	for (int i = start; i <= end; i++)
	{
		cout << array[i];
	}
	cout << '\n';
}

void ReverseArray(int* array, const int end = 0, const int start = 0)
{
	for (int i = start, j = end; i < j; i++, j--)
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
	const int SIZE = atoi(argv[1]);

	int *pi = new int[SIZE + 1];
	for (int i = 1; i <= SIZE; i++)
	{
		pi[i] = i;
	}

	unsigned int startTime = clock();
	bool elementToMoveFound = true;
	while (elementToMoveFound)
	{
		elementToMoveFound = false;
		//PrintArray(pi, SIZE, 1);
		int leftElementPosition;
		for (int i = SIZE - 1; i >= 1; i--)
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
			int minimalRightElement = SIZE + 1;
			int rightElementPosition;
			for (int i = leftElementPosition + 1; i <= SIZE; i++)
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
	unsigned int endTime = clock();
	unsigned int programWorkTime = endTime - startTime;
	cout << "Time: " << programWorkTime << endl;

    return 0;
}

