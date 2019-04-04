#ifndef __MODIFIED_ASTAR__
#define __MODIFIED_ASTAR__

#include "Dijkstra.h"

class Astar : public Dijkstra {
	using _myBase = Dijkstra;

	struct orderByAStar {
		static int row;
		static int col;
	
		// you want rhs to be smaller than lhs
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
