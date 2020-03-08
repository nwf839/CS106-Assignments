#ifndef _vector_pqueue_
#define _vector_pqueue_

#include "vector.h"
#include "pqueue.h"
#include <string>

class VectorPQueue : public PQueue {
public:
	VectorPQueue();
	~VectorPQueue();
	
	static VectorPQueue *merge(VectorPQueue *one, VectorPQueue *two);
	
	void enqueue(const std::string& elem);
    std::string extractMin();
    std::string peek() const;
	
private:
    Vector<std::string> vec;
};

#endif
