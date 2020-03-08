#include "pqueue-vector.h"
#include "error.h"

VectorPQueue::VectorPQueue() {}
VectorPQueue::~VectorPQueue() {}

std::string VectorPQueue::peek() const {
	if (logSize == 0) error("peek: Attempting to peek at an empty pqueue.");
    std::string min = vec[0];
    for (int i = 0; i < vec.size(); i++) 
    {
        if (vec[i] < min) min = vec[i];
    }
    return min;
}

std::string VectorPQueue::extractMin() {
	if (logSize == 0) error("extractMin: attempting to extract from an empty pqueue");
    std::string min;
    int minIndex;
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] < min || i == 0)
        {
            min = vec[i];
            minIndex = i;
        }
    }
    vec.remove(minIndex);
    logSize--;
	return min;
}

void VectorPQueue::enqueue(const string& elem) {
	vec.add(elem);
    logSize++;
}

VectorPQueue *VectorPQueue::merge(VectorPQueue *one, VectorPQueue *two) {
    VectorPQueue *result = new VectorPQueue;
    result->vec = one->vec + two->vec;
    result->logSize = one->logSize + two->logSize;
    return result;
}
