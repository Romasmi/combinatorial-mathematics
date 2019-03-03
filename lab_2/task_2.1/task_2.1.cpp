#include "pch.h"
#include "graph.h"
using namespace std;

int main()
{
	try
	{
		Graph graph(cin);
		graph.BFS();
		return 0;
	}
	catch (const exception& e)
	{
		cout << e.what() << '\n';
		return 1;
	}
}
