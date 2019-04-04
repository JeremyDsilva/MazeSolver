#ifndef __MODIFIED_DEPTHFIRSTSEARCH__
#define __MODIFIED_DEPTHFIRSTSEARCH__

#include "path.h"

class DepthFirstSearch : public Path {

public:
	// default constructor
	DepthFirstSearch() {}

	// destructor
	~DepthFirstSearch() {}

	void findPath(Vertex * start, Vertex * end) {
		if (intialCheck(start, end))	_findPath(start, end);
	}

private:
	bool _findPath(Vertex * start, Vertex * end) {
		if (!start || start->isVisted()) return false;

		start->setVisted(true); 
		++count;

		if (start == end) {
			path.push_front(start);
			return true;
		}
		
		for (auto & x : *start) {
			addToAnimate(start, x.getVertex());
			if (_findPath(x.getVertex(), end)) {
				path.push_front(start);
				return true;
			}
		}


		return false;
	}

};
#endif // !__DEPTHFIRSTSEARCH__
