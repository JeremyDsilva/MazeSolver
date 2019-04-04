#ifndef __MODIFIED_BREADTHFIRSTSEARCH__
#define __MODIFIED_BREADTHFIRSTSEARCH__

#include "Path.h"
#include <queue>

class BreadthFirstSearch : public Path {

public:

	void findPath(Vertex * start, Vertex * end) {
		if (!intialCheck(start, end)) return;

		count = 0;
		std::queue<Vertex*> q;
		q.push(start);
		start->setLength(0);
		Vertex* next = nullptr;

		while (!q.empty()) {
			next = q.front();
			q.pop();

			if (next->isVisted()) continue;
			++count;

			next->setVisted(true);

			if (next == end) break;

			for (auto & x :  *next) {
				if (x.isReachable() && !x.getVertex()->isVisted()) {
					q.push(x.getVertex());
					x.getVertex()->setLength(next->getLength() + 1);
					addToAnimate(next, x.getVertex());
				}
			}

		}

		if (!end->isVisted()) return; // end cannot be reached

		trace(end, start, next->getLength() - 1);

	}

private:

	bool trace(Vertex * start, Vertex * end, int count) {

		path.push_front(start);

		for (auto & x : *start) {
			if (x.isReachable() && x.getVertex()->getLength() == count) {
				trace(x.getVertex(), start, count - 1);
				return true;
			}
		}

		return false;
	}

};

#endif // !__BREADTHFIRSTSEARCH__
