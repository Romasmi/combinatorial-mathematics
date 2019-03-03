#include "pch.h"
#include "graph.h"
#include "string_processor.h"
#include "vector_processor.h"

#include <fstream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

Graph::Graph(istream& in)
{
	this->Load(in);
}

void Graph::Load(istream& in)
{
	string line;
	if (getline(in, line))
	{
		vector<size_t> params = LineToVector<size_t>(line);
		if (params.size() != Graph::inputLineParamsCount && params[0] <= Graph::maxPointsCount && params[1] <= Graph::maxEdgesCount)
		{
			//throw "Invalid input on line 1";
		}
		this->pointsCount = params[0];
		this->edgesCount = params[1];
		this->points.resize(this->pointsCount + 1);
	}
	size_t edgesCount = 0;
	vector<size_t> params;
	while (getline(in, line))
	{
		params = LineToVector<size_t>(line);
		if (params.size() != Graph::inputLineParamsCount)
		{
			//throw "Invalid input on line {edgesCount + 2}";
		}
		this->points[params[0]].adjacentPoints.push_back(params[1]);
		this->points[params[1]].adjacentPoints.push_back(params[0]);
		++edgesCount;
	}
	this->rootPointNumber = params[0];
	if (edgesCount != this->edgesCount)
	{
		//throw "Invalid edges count";
	}

	this->PrintPoints();
	this->BFS();
}

void Graph::PrintPoints()	
{
	for (size_t i = 0; i < points.size(); ++i)
	{
		PointWithAdjacentPoints point = this->points[i];
		if (point.adjacentPoints.size() != 0)
		{
			cout << i << ": ";
			Print<size_t>(point.adjacentPoints);
		}
	}
}

void Graph::BFS()
{
	AdjacentyStruct points = this->points;
	queue<size_t> queue;
	queue.push(this->rootPointNumber);
	while (!queue.empty())
	{
		size_t pointNumber = queue.front();
		queue.pop();
		points[pointNumber].color = Color::BLACK;
		for (size_t pointNumber : points[pointNumber].adjacentPoints)
		{
			if (points[pointNumber].color == Color::WHITE)
			{
				queue.push(pointNumber);
				points[pointNumber].color = Color::GREY;
			}
		}
		cout << pointNumber << '\n';
	}
}

void Graph::DFS()
{

}