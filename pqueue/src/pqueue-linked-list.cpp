#include "pqueue-linked-list.h"
#include "error.h"

LinkedListPQueue::LinkedListPQueue() 
{
    head = tail = NULL;
}

LinkedListPQueue::~LinkedListPQueue() 
{
    while(head != NULL)
    {
        Cell *tmp = head;
        head = head->next;
        delete tmp;
    }
}

std::string LinkedListPQueue::peek() const 
{
    if (head == NULL) error("peek(): Attempting to peek at an empty pqueue");
	return head->elem;
}

std::string LinkedListPQueue::extractMin() 
{
	if (head == NULL) error("extractMin(): Attempting to extract from an empty pqueue");
    logSize--;
    std::string min = peek();
    Cell *tmp = head;
    head = head->next;
    delete tmp;
	return min;
}

void LinkedListPQueue::enqueue(const std::string& elem) 
{
    logSize++;
    Cell *cp = new Cell;
    cp->elem = elem;
    if (head == NULL)
    {
        cp->next = NULL;
        cp->prev = NULL;
        tail = head = cp;
    }

    if (elem < head->elem)
    {
        cp->next = head;
        cp->prev = NULL;
        head->prev = cp;
        head = cp;
    }
    else if (elem >= tail->elem)
    {
        cp->next = NULL;
        cp->prev = tail;
        tail->next = cp;
        tail = cp;
    }
    else
    {
        Cell *cursor = head;
        while (cursor != NULL && elem >= cursor->elem) cursor = cursor->next;
        cp->next = cursor;
        cp->prev = cursor->prev;
        cursor->prev->next = cp;
        cursor->prev = cp;
    }
}

LinkedListPQueue *LinkedListPQueue::merge(LinkedListPQueue *one, LinkedListPQueue *two) 
{
    LinkedListPQueue *result = new LinkedListPQueue;
    while (one->head != NULL)
    {
        result->enqueue(one->extractMin());
    }
    while (two->head != NULL)
    {
        result->enqueue(two->extractMin());
    }
    return result;
}
