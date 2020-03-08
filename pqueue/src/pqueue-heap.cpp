#include "pqueue-heap.h"
#include "error.h"

HeapPQueue::HeapPQueue() {
    capacity = INITIAL_CAPACITY;
    heap = new std::string[capacity];
    logSize = 0;
}
HeapPQueue::~HeapPQueue() {
    delete[] heap;
    logSize = 0;
}

std::string HeapPQueue::peek() const {
	if (logSize == 0) error("peek(): Attempting to peek at an empty pqueue.");
    return heap[0];
}

std::string HeapPQueue::extractMin() {
	if (logSize == 0) error("extractMin(): Attempting to extract from an empty pqueue.");
    std::string min = heap[0];
    heap[0] = heap[--logSize];
    int index = 0;
    int left = 0;
    int right = -1;
    int high = -1;
    int low = 0;
    while (true)
    {
        left = 2 * index + 1;
        right = 2 * index + 2;
        if (left >= logSize) break;
        if (right >= logSize)
        {
            low = left;
            high = right = -1;
        }
        else
        {
            low = (heap[left] < heap[right]) ? left : right;
            high = (heap[left] < heap[right]) ? right : left;
        }


        if (heap[index] > heap[low])
        {
            swap(heap[index], heap[low]);
            index = low;
        }
        else if (high != -1 && heap[index] > heap[high])
        {
            swap(heap[index], heap[high]);
            index = high;
        }
        else break;
    }
    return min;
}

void HeapPQueue::enqueue(const std::string& elem) {
    if (size() == capacity) expandCapacity();
    heap[logSize++] = elem;
    int index = logSize - 1;
    while (heap[index] < heap[(index - 1) / 2])
    {
        swap(heap[index], heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

HeapPQueue *HeapPQueue::merge(HeapPQueue *one, HeapPQueue *two) {
    HeapPQueue *result = new HeapPQueue;
    std::string *oldHeap = result->heap;
    result->capacity = one->capacity + two->capacity;
    result->heap = new std::string[result->capacity];
    delete[] oldHeap;
    for (int i = 0; i < one->size(); i++)
    {
        result->heap[result->logSize++] = one->heap[i];
    }
    delete one;
    for (int i = 0; i < two->size(); i++)
    {
        result->heap[result->logSize++] = two->heap[i];
    }
    delete two;
    for (int i = result->size() - 1; i >= 0; i--)
    {
        result->heapify(i);
    }
	return result;
}

void HeapPQueue::expandCapacity()
{
    std::string *oldHeap = heap;
    capacity *= 2;
    heap = new std::string[capacity];
    for (int i = 0; i < logSize; i++)
    {
        heap[i] = oldHeap[i];
    }
    delete[] oldHeap;
}

void HeapPQueue::heapify(int root)
{   
    int left = 2 * root + 1;
    if (left >= size()) return;
    
    int right = left + 1 < size() ? left + 1 : left;
    int min;

    if (heap[left] <= heap[root]) min = left;
    else min = root;

    if (heap[right] <= heap[root] && heap[right] < heap[min]) min = right;

    if (min != root)
    {
        swap(heap[min], heap[root]);
        heapify(min);
    }
}


void HeapPQueue::swap(std::string &str1, std::string &str2)
{
    std::string tmp = str1;
    str1 = str2;
    str2 = tmp;
}
