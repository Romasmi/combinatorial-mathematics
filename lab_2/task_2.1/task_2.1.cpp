#include "pch.h"

#include "graph.h"
#include "vector_processor.h"
using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		if (argc == 2)
		{
			ifstream file("input.txt");
			Graph graph(file);
			Print<size_t>(graph.GetCutVerticles());
			graph.PrintBridges();
		}
		else
		{
			Graph graph(cin);
			Print<size_t>(graph.GetCutVerticles());
			graph.PrintBridges();
		}
		return 0;
	}
	catch (const exception& e)
	{
		cout << e.what() << '\n';
		return 1;
	}
}
