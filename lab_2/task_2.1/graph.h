#pragma once;

#include <fstream>
#include <vector>

enum Color
{
	WHITE,
	GREY,
	BLACK
};

using AdjacentPoints = std::vector<size_t>;

struct PointWithAdjacentPoints
{
	size_t inTime;
	size_t outTime;
	Color color = WHITE;
	AdjacentPoints adjacentPoints;
};

using AdjacentyStruct = std::vector<PointWithAdjacentPoints>;

class Graph
{
public:
	Graph(std::istream& in);
	void PrintPoints();
	void BFS();
	void DFS();
	void PrintCutVeticles();
	static bool IsParent(const PointWithAdjacentPoints& parent, const PointWithAdjacentPoints& child);

private:
	AdjacentyStruct points;
	size_t edgesCount;
	size_t pointsCount;
	size_t rootPointNumber;

	static const size_t inputLineParamsCount = 2;
	static const size_t maxPointsCount = 400;
	static const size_t maxEdgesCount = Graph::maxPointsCount * (Graph::maxPointsCount - 1) / 2;

protected:
	void Load(std::istream& in);

};
