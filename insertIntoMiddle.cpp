#include "List2.h"
#include <iostream>
using namespace std;




void FineGrainedQueue::insertIntoMiddle(int value, int pos)
{
    Node* newNode = new Node(value);
    
    queue_mutex->lock();
    
    if (head == nullptr)
    {
        head = newNode;
        queue_mutex->unlock();
        return;
    }

    if (pos == 0)
    {
        newNode->next = head;
        head = newNode;
        queue_mutex->unlock();
        return;
    }

    Node* current = head;

    current->node_mutex->lock();

    queue_mutex->unlock();

    int currPos = 0;

    while (currPos < pos - 1 && current->next != nullptr)
    {
        Node* old_cur = current;
        current = current->next;
        if (current)
            current->node_mutex->lock();
        currPos++;
        old_cur->node_mutex->unlock();
    }

    Node* next = current->next;
    if (next)
        next->node_mutex->lock();
    current->next = newNode;
    newNode->next = next;
    if (next)
        next->node_mutex->unlock();

    current->node_mutex->unlock();

}