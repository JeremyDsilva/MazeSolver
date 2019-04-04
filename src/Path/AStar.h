#ifndef __ASTAR__
#define __ASTAR__

#include "Dijkstra.h"

class Astar : public Dijkstra {
	using _myBase = Dijkstra;

	struct orderByAStar {
		// final position
		static int row;
		static int col;
	
		bool operator()(Vertex *lhs, Vertex* rhs) {
		     return abs(col - rhs->getColumn() * 1.0) + abs(row - rhs->getRow() *1.0) + rhs->getLength() < abs(col - lhs->getColumn() * 1.0) + abs(row - lhs->getRow()) +  lhs->getLength();
		}
	};

public:

	void findPath(Vertex * start, Vertex * end) {
		if (!intialCheck(start, end)) return;

		orderByAStar::col = end->getColumn();
		orderByAStar::row = end->getRow();

		start->setLength(0);
		_myBase::_findPath<orderByAStar>(start, end);
	}

};

// Astar::orderByAsar static declarations
int Astar::orderByAStar::row = 0;
int Astar::orderByAStar::col = 0;

#endif // !__ASTAR__
