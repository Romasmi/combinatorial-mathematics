#include "pch.h"

#include "graph.h"
#include "string_processor.h"
#include "util.h"
#include "vector_processor.h"

#include <fstream>
#include <queue>
#include <stack>
#include <string>

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
}

void Graph::PrintPoints()
{
	for (size_t i = 0; i < points.size(); ++i)
	{
		PointWithAdjacentPoints point = this->points[i];
		if (!point.adjacentPoints.empty())
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
	AdjacentyStruct points = this->points;
	size_t time = 1;
	stack<size_t> stack;
	stack.push(this->rootPointNumber);
	points[this->rootPointNumber].inTime = time;
	points[this->rootPointNumber].color = Color::GREY;
	while (!stack.empty())
	{
		size_t pointNumber = stack.top();
		stack.pop();

		if (points[pointNumber].color == Color::BLACK)
		{
			continue;
		}

		if (points[pointNumber].color != Color::GREY)
		{
			points[pointNumber].color = Color::GREY;
			points[pointNumber].inTime = ++time;
		}
		stack.push(pointNumber);

		bool hasWhiteAdjacentPoints = false;
		for (size_t pointNumber : points[pointNumber].adjacentPoints)
		{
			if (points[pointNumber].color == Color::WHITE)
			{
				stack.push(pointNumber);
				hasWhiteAdjacentPoints = true;
			}
		}
		if (!hasWhiteAdjacentPoints)
		{
			stack.pop();
			points[pointNumber].color = Color::BLACK;
			points[pointNumber].outTime = ++time;
			cout << pointNumber << " [" << points[pointNumber].inTime << ':' << points[pointNumber].outTime << "]\n";
		}
	}
}

bool Graph::IsParent(const PointWithAdjacentPoints& parent, const PointWithAdjacentPoints& child)
{
	return parent.inTime < child.inTime && parent.outTime > child.outTime;
}

vector<size_t> Graph::GetCutVerticles()
{
	if (!this->cutVetirclesFound)
	{
		AdjacentyStruct points = this->points;
		size_t time = 1;
		stack<size_t> stack;
		stack.push(this->rootPointNumber);
		points[this->rootPointNumber].inTime = time;
		points[this->rootPointNumber].color = Color::GREY;

		vector<bool> cutVeticles(points.size());
		vector<size_t> up(points.size());
		fill(up.begin(), up.end(), 1);
		vector<size_t> parent(points.size());
		size_t rootChildsCount = 0;

		while (!stack.empty())
		{
			size_t pointNumber = stack.top();
			stack.pop();

			if (points[pointNumber].color == Color::WHITE)
			{
				points[pointNumber].color = Color::GREY;
				points[pointNumber].inTime = ++time;
				up[pointNumber] = points[pointNumber].inTime;
			}
			if (points[pointNumber].color != Color::BLACK)
			{
				stack.push(pointNumber);
			}

			bool hasWhiteAdjacentPoints = false;
			bool upIsSet = false;
			size_t minUp = this->pointsCount * this->pointsCount;
			for (size_t adjacentPointNumber : points[pointNumber].adjacentPoints)
			{
				if (points[adjacentPointNumber].color == Color::WHITE)
				{
					parent[adjacentPointNumber] = pointNumber;
					stack.push(adjacentPointNumber);
					hasWhiteAdjacentPoints = true;
				}
				else if (parent[pointNumber] != adjacentPointNumber)
				{
					if (points[adjacentPointNumber].color != Color::BLACK)
					{
						up[pointNumber] = Min<size_t>(up[pointNumber], up[adjacentPointNumber]);
					}
					else
					{
						upIsSet = true;
						size_t pointUp = Min<size_t>(up[pointNumber], up[adjacentPointNumber]);
						if (pointUp >= points[pointNumber].inTime && pointNumber != this->rootPointNumber)
						{
							this->points[pointNumber].isCutVeticle = true;
						}
						if (pointUp < minUp)
						{
							minUp = pointUp;
						}
					}
				}
				int a = 1;
			}
			if (upIsSet)
			{
				up[pointNumber] = minUp;
			}

			if (!hasWhiteAdjacentPoints && points[pointNumber].color != Color::BLACK)
			{
				stack.pop();
				points[pointNumber].color = Color::BLACK;
			}
		}

		for (size_t pointNumber : points[this->rootPointNumber].adjacentPoints)
		{
			if (up[pointNumber] != up[this->rootPointNumber])
			{
				++rootChildsCount;
			}
			if (rootChildsCount == 2)
			{
				cutVeticles[this->rootPointNumber] = true;
				break;
			}
		}
	}

	vector<size_t> cutVeticles;
	for (size_t i = 0; i < this->points.size(); ++i)
	{
		if (this->points[i].isCutVeticle)
		{
			cutVeticles.push_back(i);
		}
	}
	return cutVeticles;
}

void Graph::PrintBridges()
{
	vector<size_t> cutVerticles = this->GetCutVerticles();
	for (size_t cutVerticle : cutVerticles)
	{
		for (size_t adjacentPointNumber : this->points[cutVerticle].adjacentPoints)
		{
			if (this->points[adjacentPointNumber].isCutVeticle ||
				this->points[adjacentPointNumber].adjacentPoints.size() > 1)
			{
				cout << cutVerticle << " : " << adjacentPointNumber << '\n';
			}
		}
	}
}
