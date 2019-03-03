#include "pch.h"
#include "graph.h"
using namespace std;

int main()
{
	try
	{
		Graph graph(cin);
	}
	catch (const exception& e)
	{
		cout << e.what() << '\n';
	}
}
