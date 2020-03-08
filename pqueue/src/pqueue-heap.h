#ifndef _binary_heap_pqueue_
#define _binary_heap_pqueue_

#include "pqueue.h"
#include <string>

class HeapPQueue : public PQueue {
public:
	HeapPQueue();
	~HeapPQueue();
	
	static HeapPQueue *merge(HeapPQueue *one, HeapPQueue *two);
	
	void enqueue(const std::string& elem);
    std::string extractMin();
    std::string peek() const;
    
private:


/* Private constants */
    
    static int const INITIAL_CAPACITY = 10;

/* Instance variables */

    std::string *heap;
    int capacity;

/* Private methods */

    void expandCapacity();
    void swap(std::string &str1, std::string &str2);
    void heapify(int root);
    
};

#endif
