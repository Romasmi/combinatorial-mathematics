#include "pch.h"
#include "graph.h"
using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		if (argc == 2)
		{
			ifstream file("input.txt");
			Graph graph(file);
			graph.PrintCutVeticles();
		}
		else
		{
			Graph graph(cin);
			graph.PrintCutVeticles();
		}
		return 0;
	}
	catch (const exception& e)
	{
		cout << e.what() << '\n';
		return 1;
	}
}
