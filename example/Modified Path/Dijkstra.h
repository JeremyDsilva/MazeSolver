#ifndef __MODIFIED_DIJKSTRA__
#define __MODIFIED_DIJKSTRA__

#include "Path.h"
#include <queue>

class Dijkstra : public Path {
	using _myBase = Path;

private:

	struct orderByDijkstra {
		bool operator()(Vertex *lhs, Vertex* rhs) {
			return rhs->getLength() < lhs->getLength();
		}
	};

public:

	void findPath(Vertex * start, Vertex * end) {
		if (!intialCheck(start, end)) return;
		start->setLength(0);
		_findPath<orderByDijkstra>(start, end);
	}

protected:

	int setDistance(Vertex* from, Vertex* to, int toLen = 1) {
		to->setLength(to->getLength() > from->getLength() + toLen ? from->getLength() + toLen : to->getLength());
		return to->getLength();
	}

	template <class comparator>
	void _findPath(Vertex * start, Vertex * end) {
		std::priority_queue<Vertex*, std::vector<Vertex*>, comparator> q;
		q.push(start);
		Vertex* next = nullptr;

		while (!q.empty()) {

			next = q.top();
			q.pop();

			if (next->isVisted()) continue;

			next->setVisted(true);
			++count;

			if (next == end) break;

			for (auto & x : *next) {
				if (x.isReachable() && !x.getVertex()->isVisted()) {
					setDistance(next, x.getVertex(), x.getEdgeLength());
					q.push(x.getVertex());
					addToAnimate(next, x.getVertex());
				}
			}

		}

		trace(start, end);

	}

	void trace(Vertex * start, Vertex * end) {

		if (!end->isVisted()) return; // cannot reach end

		int min = 0;
		Vertex * next = end, *buffer = nullptr;
		path.push_front(next);
		while (next != start) {
			min = next->getLength();

			for (auto & x : *next) {
				if (x.isReachable() && min > x.getVertex()->getLength()) {
					buffer = x.getVertex();
					min = x.getVertex()->getLength();
				}
			}

			path.push_front(buffer);
			next = buffer;
		}

	}

};

#endif // !__DIJKSTRA__
