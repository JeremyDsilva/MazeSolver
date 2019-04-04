#ifndef __PATH__
#define __PATH__

#include <list>
#include <queue>
#include "../../src/Vertex.h"

using std::list;
using std::queue;

struct Travel {
	Vertex* from;
	Vertex* to;
};

class Path {

protected:
	list<Vertex*> path; // path from start to end
	int count = 0; // used for iteration count
	queue<Travel> visted;

	void addToAnimate(Vertex * from, Vertex * to) {

		if (to && to->isVisted()) return;

		Travel topush;
		topush.from = from;
		topush.to = to;
		visted.push(topush);
	}
	
	/*
		Inital check done before path finding 

		Parameters
		Start end : postion to start to end

		return true if specified path finding should continue
	*/
	bool intialCheck(Vertex * start, Vertex * end) {
		if (!start || !end)	// if start or end are nullptr path doesnot exist
			return false;

		if (start == end) { // if start equals end path found return false
			path.push_back(start);
			return false;
		}

		return true; // find path 
	}

public:
	// default constructor
	Path() {}

	//default 
	~Path() {
		path.clear();
	}


	// findPath function to implement path specific algorithm
	virtual void findPath(Vertex * start, Vertex * end) = 0;

	// return count
	int getCount() {
		return count;
	}

	// get path
	const list<Vertex*> & getPath() {
		return path;
	}

	queue<Travel>& getVisted() {
		return visted;
	}

	// get coordinates
	list<Coordinates> getCordinatePath() {
		list<Coordinates> toReturn;
		if (path.empty()) return toReturn;

		Vertex * start = *getPath().begin();
		Coordinates to_push;
		to_push.row = start->getRow(); to_push.col = start->getColumn();
		toReturn.push_back(to_push);

		auto it = ++getPath().begin();
		while (it != getPath().end()) {	
			for (auto & x : start->connectingEdge(*it)) {
				toReturn.push_back(x);
			}
			to_push.row = (*it)->getRow(); to_push.col = (*it)->getColumn();
			toReturn.push_back(to_push);
			start = *it++;
		}
		return toReturn;
	}


};
#endif // !__PATH__
