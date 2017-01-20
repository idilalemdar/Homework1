#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include "Node.hpp"

using namespace std;

template <class T> 
class LinkedList {
    private:
        Node<T>* front;
        Node<T>* back;

    public:

        LinkedList();
        LinkedList(const LinkedList<T>& ll);
        LinkedList<T>& operator=(const LinkedList<T>& ll);
        ~LinkedList();

        Node<T>& getFront() const;
        Node<T>& getBack() const;
        Node<T>& getNodeAt(int pos) const;
        Node<T>* getNodePtrAt(int pos) const;

        void insert(Node<T>* prev, const T& data);
        void insertAt(int pos, const T& data);
        void erase(Node<T>* node);
        void eraseFrom(int pos);
        void clear();
        void pushFront(const T& data);
        void pushBack(const T& data);
        void popFront();
        void popBack();
        bool isEmpty() const;
        size_t getSize() const;
        void print() const;
};

template <class T>
LinkedList<T>::LinkedList() : front(0), back(0) {}	 	  	  	 	  	  	        	 	

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll) 
{
    front = back = 0;
    *this = ll;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll)
{
    if(this != &ll)
    {
        clear();
        Node<T> *np = &(ll.getFront());
        while(np)
        {
            insert(back,np->getData());
            np = np->getNext();
        }   
    }
    return *this;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    clear();
    delete front;
    delete back;
}

template <class T>
Node<T>& LinkedList<T>::getFront() const
{	 	  	  	 	  	  	        	 	
    return *front;
}

template <class T>
Node<T>& LinkedList<T>::getBack() const
{
    return *back;
}

template <class T>
Node<T>& LinkedList<T>::getNodeAt(int pos) const
{
    return *getNodePtrAt(pos);
}

template <class T>
Node<T>* LinkedList<T>::getNodePtrAt(int pos) const
{
    if(pos < 0 || !front)
    {
        throw runtime_error("invalid index");
    }
    Node<T>* tmp = front;
    for(int i = 0; i < pos; i++)
    {	 	  	  	 	  	  	        	 	
        tmp = tmp->getNext();
        if(!tmp)
        {
            throw runtime_error("invalid index");
        }
    }
    return tmp;
}

template <class T>
void LinkedList<T>::insert(Node<T>* prev, const T& data)
{
    Node<T>* newnode = new Node<T>(data); //insert as the first node
    if(isEmpty())
    {
        if(!prev)
        {
            front = newnode;
            back = newnode;
        }
        else throw runtime_error("invalid operation");
    }
    else if(!prev) // insert as front node
    {
        newnode->setNext(front);
        front->setPrev(newnode);
        front = newnode;
    }
    else if(!prev->getNext()) //insert as back node
    {
        newnode->setPrev(back);
        back->setNext(newnode);
        back = newnode;
    }
    else //insert in the middle
    {	 	  	  	 	  	  	        	 	
        newnode->setPrev(prev);
        newnode->setNext(prev->getNext());
        prev->setNext(newnode);
        newnode->getNext()->setPrev(newnode);
    }
}

template <class T>
void LinkedList<T>::insertAt(int pos, const T& data)
{
    if(pos < 0)
    {
        throw runtime_error("invalid index");
    }
    else if(!pos)
    {
        insert(0, data);
    }
    else if(pos && isEmpty())
    {
        throw runtime_error("invalid operation");
    }
    else
    {
        Node<T>* tmp = front;
        int i = 0;
        for(; i < pos; i++)
        { 
            if(!tmp->getNext()) break;
            else
            {
                tmp = tmp->getNext();
            }
        }
        if(tmp->getNext()) //valid indexs
        {	 	  	  	 	  	  	        	 	
            return insert(tmp->getPrev(), data);
        }
        else if(!tmp->getNext() && i == pos)
        {
            return insert(back->getPrev(),data);
        }
        else if(!tmp->getNext() && i == pos - 1) // insert to the back
        {
            return insert(back, data);
        }
        else
        {
            throw runtime_error("invalid index");
        }
    }
}

template <class T>
void LinkedList<T>::erase(Node<T>* node)
{
    if(isEmpty())
    {
        throw runtime_error("empty list");
    }
    else if(!node)
    {
        throw runtime_error("invalid operation");
    }
    else
    {
        Node<T>* tmp = node;
        if(node == front && node == back) //there is only one node in the list
        {
            front = 0;
            back = 0;
        }	 	  	  	 	  	  	        	 	
        else if(node == front) //erase first node
        {
            front = front->getNext();
            front->setPrev(0);
            tmp->setNext(0);
        }
        else if(node == back) //erase last node
        {
            back = back->getPrev();
            back->setNext(0);
            tmp->setPrev(0);
        }
        else //erase from the middle
        {
            tmp->getNext()->setPrev(tmp->getPrev());
            tmp->getPrev()->setNext(tmp->getNext());
            tmp->setPrev(0);
            tmp->setNext(0);
        }
        delete tmp;
    }
}

template <class T>
void LinkedList<T>::eraseFrom(int pos)
{
    if(pos < 0)
    {
        throw runtime_error("invalid index");
    }
    else if(!pos)
    {
        erase(front);
    }
    else if(!isEmpty())
    {	 	  	  	 	  	  	        	 	
        Node<T>* tmp = front;
        for(int i = 0; i < pos; i++)
        {
            tmp = tmp->getNext();
            if(!tmp) break;
        }
        if(tmp) 
        {
            erase(tmp);
        }
        else 
        {
            throw runtime_error("invalid index");
        }
    }
    else throw runtime_error("invalid operation");
}

template <class T>
void LinkedList<T>::clear()
{
    while(!isEmpty())
    {
        erase(back);
    }
}

template <class T>
void LinkedList<T>::pushFront(const T& data)
{
    insert(0, data);
}

template <class T>
void LinkedList<T>::pushBack(const T& data)
{	 	  	  	 	  	  	        	 	
    insert(back, data);
}

template <class T>
void LinkedList<T>::popFront()
{
    erase(front);
}

template <class T>
void LinkedList<T>::popBack()
{
    erase(back);
}

template <class T>
bool LinkedList<T>::isEmpty() const
{
    return !(front || back);
}

template <class T>
size_t LinkedList<T>::getSize() const
{
    Node<T>* tmp = front;
    int count = 0;
    while(tmp)
    {
        tmp = tmp->getNext();;
        count++;
    }
    return count;
}

template <class T>
void LinkedList<T>::print() const
{	 	  	  	 	  	  	        	 	
    Node<T>* tmp = front;
    while(tmp)
    {
        cout << tmp->getData() << endl;
        tmp = tmp->getNext();
    }
}

#endif