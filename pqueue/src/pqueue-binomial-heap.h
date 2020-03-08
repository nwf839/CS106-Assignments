#ifndef _binomial_heap_pqueue_
#define _binomial_heap_pqueue_

#include "pqueue.h"
#include <string>
#include "vector.h"

class BinomialHeapPQueue : public PQueue {
public:
	BinomialHeapPQueue();
	~BinomialHeapPQueue();
	
	static BinomialHeapPQueue *merge(BinomialHeapPQueue *one, BinomialHeapPQueue *two);
	
	void enqueue(const std::string& elem);
    std::string extractMin();
    std::string peek() const;
	
private:
    
/* Types */
    
    struct node {
        std::string elem;
        Vector<node *> children;
    };

/* Instance variables */
    
    Vector<node *> root;

/* Private methods */

    int findMinIndex(const Vector<node *> &vec) const;
    node *mergeTrees(node *tree1, node *tree2);
    void addTree(int index, node *tree);
    void swap(std::string &str1, std::string &str2);
    void clear(Vector<node *> &vec);
};

#endif
