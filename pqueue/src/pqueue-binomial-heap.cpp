#include "pqueue-binomial-heap.h"
#include "error.h"
#include "vector.h"

BinomialHeapPQueue::BinomialHeapPQueue() {}

BinomialHeapPQueue::~BinomialHeapPQueue() 
{
    clear(root);
    logSize = 0;
}


std::string BinomialHeapPQueue::peek() const {
    if (size() == 0) error("peek(): Attempting to peek at an empty pqueue");
	return root[findMinIndex(root)]->elem;
}

std::string BinomialHeapPQueue::extractMin() 
{
    if (size() == 0) error("extractMin(): Attempting to extract from an empty pqueue");
    // Find the index of the minimum value by performing a linear search of the root vector
    int minIndexRoot = findMinIndex(root);
    // Sets a pointer to the node containing the binomial heap whose root is the minimum
    // and saves it in a string
    node *minNode = root[minIndexRoot];
    std::string minElem = minNode->elem;
    root[minIndexRoot] = NULL;


    // Finds the index of the minimum value of the min node's children vector
    if (minNode->children.size() == 0)
    {
        minNode = NULL;
        logSize--;
        return minElem;
    }

    // Loop through min node's vector
    // ------------------------------
    // Goes through each node in min node's vector, ignoring NULL values and the value of
    // of its own min.
    //
    // Uses the enqueue method's recursive helper method to add each of these the the min
    // node's children to it's own minimum node's children, and then sets the respective
    // pointer in minNode's children vector to NULL
    for (int i = 0; i < minNode->children.size(); i++)
    {
        node *minChild = minNode->children[i];
        if (minNode != NULL)
        {
            addTree(minChild->children.size(), minChild);
        }
    }

    // Because the size of the binomial heap was decreased by one it needs
    // to be moved backward one position in the root

    logSize--;
    return minElem;
}

void BinomialHeapPQueue::enqueue(const string& elem) 
{
    node *child = new node;
    child->elem = elem;
    addTree(0, child);
    logSize++;
}


BinomialHeapPQueue *BinomialHeapPQueue::merge(BinomialHeapPQueue *one, BinomialHeapPQueue *two) {
	BinomialHeapPQueue *result = new BinomialHeapPQueue;
    int oneSize = one->size();
    int twoSize = two->size();
    int loopBound = oneSize < twoSize ? twoSize : oneSize;
    if (oneSize < twoSize)
        while (one->size() < twoSize) one->root.add(NULL);
    else
        while (two->size() < oneSize) two->root.add(NULL);

    node *tree = NULL;
    for (int i = 0; i < loopBound; i++)
    {
        if (one->root[i] == NULL) tree = two->root[i];
        else if (two->root[i] == NULL) tree = one->root[i];
        else if (one->root[i] != NULL && two->root[i] != NULL) result->mergeTrees(one->root[i], two->root[i]);
        
        if (tree != NULL) result->addTree(tree->children.size() + 1, tree);
        else
            while (result->size() < i) result->root.add(NULL);
        result->logSize++;
    }   
    return result;
}    

int BinomialHeapPQueue::findMinIndex(const Vector<node *> &vec) const
{
    if (vec.size() == 0) return -1;

    int i = 0;
    while (vec[i] == NULL) i++;
    if (i == vec.size()) return -1;
    
    int minIndex = i;
    std::string minElem = vec[i]->elem;
    for (++i; i < vec.size(); i++)
    {
        if (vec[i] != NULL)
        {
            if (vec[i]->elem < minElem)
            {
                minIndex = i;
                minElem = vec[i]->elem;
            }
        }
    }
    return minIndex;
}

void BinomialHeapPQueue::addTree(int index, node *tree)
{
    while (root.size() <= index) root.add(NULL);

    if (root[index] == NULL) root[index] = tree;
    else
    {
        tree = mergeTrees(root[index], tree);
        root[index] = NULL;
        addTree(index + 1, tree);
    }
}

BinomialHeapPQueue::node *BinomialHeapPQueue::mergeTrees(node *tree1, node *tree2)
{
    if (tree2->elem < tree1->elem) return mergeTrees(tree2, tree1);
    tree1->children.add(tree2);
    return tree1;
}

void BinomialHeapPQueue::swap(std::string &str1, std::string &str2)
{
    std::string tmp = str1;
    str1 = str2;
    str2 = tmp;
}


void BinomialHeapPQueue::clear(Vector<node *> &vec) 
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] != NULL) 
        {
            clear(vec[i]->children);
            delete vec[i];
        }
    }
}
