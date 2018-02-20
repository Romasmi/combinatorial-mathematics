#include "stdafx.h"
using namespace std;
int main()
{
	int N = 4;
	int K = 2;
	vector<int> combination(K + 1);

	combination[0] = -1;
	for (int i = 1; i <= K; ++i)
	{
		combination[i] = i;
	}

	int j = 1;
	while (j != 0)
	{
		copy(combination.begin() + 1, combination.end(), ostream_iterator<int>(cout, " "));
		cout << "\n";

		j = K;
		while (combination[j] == N - K + j)
		{
			--j;
		}
		++combination[j];

		for (int i = j + 1; i <= K; ++i)
		{
			combination[i] = combination[i - 1] + 1;
		}
	}

    return 0;
}

