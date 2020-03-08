#ifndef _linked_list_pqueue_
#define _linked_list_pqueue_

#include "pqueue.h"
#include <string>

class LinkedListPQueue : public PQueue {
public:
	LinkedListPQueue();
	~LinkedListPQueue();
	
	static LinkedListPQueue *merge(LinkedListPQueue *one, LinkedListPQueue *two);
	
	void enqueue(const std::string& elem);
    std::string extractMin();
    std::string peek() const;
	
private:
	
/* Types */

    struct Cell {
        std::string elem;
        Cell *next;
        Cell *prev;
    };

/* Instance variables */

    Cell* head;
    Cell* tail;

};

#endif
