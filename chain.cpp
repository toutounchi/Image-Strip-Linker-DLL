#include "chain.h"
#include <cmath>
#include <iostream>

// PA1 functions
// Complete all of the missing implementation
// and submit this file for grading.

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain()
{
    Clear();
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node *Chain::InsertAfter(Node *p, const Block &ndata)
{
    Node *newNode = new Node(ndata);
    length_++;

    if (p == nullptr)
    {
        if (head_ != nullptr)
        {
            newNode->next = head_;
            head_->prev = newNode;
        }
        head_ = newNode;
    }
    else
    {
        newNode->next = p->next;
        newNode->prev = p;
        if (p->next != nullptr)
        {
            p->next->prev = newNode;
        }
        p->next = newNode;
    }
    return newNode;
}

/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::Swap(Node *p, Node *q)
{
    if (p == nullptr || q == nullptr || p == q)
    {
        return;
    }

    if (p->next == q)
    {
        p->next = q->next;
        if (q->next)
        {
            q->next->prev = p;
        }
        q->prev = p->prev;
        if (p->prev)
        {
            p->prev->next = q;
        }
        q->next = p;
        p->prev = q;
    }
    else if (q->next == p)
    {
        q->next = p->next;
        if (p->next)
        {
            p->next->prev = q;
        }
        p->prev = q->prev;
        if (q->prev)
        {
            q->prev->next = p;
        }
        p->next = q;
        q->prev = p;
    }
    else
    {
        Node *pNext = p->next;
        Node *pPrev = p->prev;
        Node *qNext = q->next;
        Node *qPrev = q->prev;

        p->next = qNext;
        if (qNext)
            qNext->prev = p;

        q->next = pNext;
        if (pNext)
            pNext->prev = q;

        p->prev = qPrev;
        if (qPrev)
            qPrev->next = p;

        q->prev = pPrev;
        if (pPrev)
            pPrev->next = q;
    }

    if (head_ == p)
    {
        head_ = q;
    }
    else if (head_ == q)
    {
        head_ = p;
    }
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::Clear()
{
    Node *current = head_;
    while (current != nullptr)
    {
        Node *temp = current;
        current = current->next;
        delete temp;
    }
    head_ = NULL;
    length_ = 0;
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::Copy(Chain const &other)
{
    if (other.head_ == nullptr)
    {
        Clear();
        head_ = nullptr;
        length_ = 0;
        return;
    }

    // Makiing sure the current chain is clear
    Clear();
    head_ = new Node(other.head_->data);

    Node *current = head_;
    Node *otherCurrent = other.head_->next;

    // iterate over the chain to be copied into current
    while (otherCurrent != nullptr)
    {
        current->next = new Node(otherCurrent->data);
        current->next->prev = current;
        current = current->next;
        otherCurrent = otherCurrent->next;
    }

    length_ = other.length_;
}

/**
 * Takes the current chain and renders it into a
 * correctly sized PNG. The blocks in the chain
 * are placed in the image left to right in order
 * of their occurrence in the chain.
 */
PNG Chain::Render()
{
    if (head_ == nullptr)
        return PNG();

    int height = head_->data.Height();
    int width = 0;
    Node *curr = head_;
    while (curr)
    {
        width += curr->data.Width();
        curr = curr->next;
    }

    PNG image(width, height);

    Node *temp = head_;
    int x = 0;
    while (temp != nullptr)
    {
        temp->data.Render(image, x);
        x += temp->data.Width();
        temp = temp->next;
    }

    return image;
}

/* Modifies the current chain:
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block
 *	is big for all other blocks.
 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::Unscramble()
{

    // If the list is empty or has only one block there is no point of unscarmbling.
    if (head_ == nullptr || head_->next == nullptr)
    {
        return;
    }

    Node *leftNode = head_;
    double maxDist = -1;

    Node *current = head_;
    while (current != nullptr)
    {
        double minDist = 1e9;

        Node *temp = head_;
        while (temp != nullptr)
        {
            if (current != temp)
            {
                minDist = std::min(minDist, temp->data.DistanceTo(current->data));
            }
            temp = temp->next;
        }

        if (minDist > maxDist)
        {
            maxDist = minDist;
            leftNode = current;
        }

        current = current->next;
    }

    Swap(head_, leftNode);

    Node *sorted = head_;
    while (sorted->next != nullptr)
    {
        Node *bestMatch = sorted->next;
        double bestDist = 1e9;

        Node *found = sorted->next;
        while (found != nullptr)
        {
            double dist = sorted->data.DistanceTo(found->data);
            if (dist < bestDist)
            {
                bestDist = dist;
                bestMatch = found;
            }
            found = found->next;
        }

        Swap(sorted->next, bestMatch);
        sorted = sorted->next;
    }
}

