#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>
#include <cstddef>
#include <stdexcept>

using namespace std;

template <class T> 
class Stack 
{
    private:
        T* items;
        size_t size;
        size_t capacity;

    public:
        Stack(int capacity=8);
        Stack(const Stack<T>& stack);
        Stack<T>& operator=(const Stack<T>& stack);
        ~Stack();
        void push(const T& item);
        T pop();
        const T& top() const;
        void clear();
        bool isEmpty() const;
        size_t getSize() const;
        size_t getCapacity() const;
        void print() const;
        void printReversed() const;
};

template <class T>
Stack<T>::Stack(int capacity) : capacity(capacity), size(0)
{
    items = new T[capacity];
}

template <class T>
Stack<T>::Stack(const Stack<T>& stack)
{
    items = new T[stack.capacity];
    size = stack.size;
    capacity = stack.capacity;
    for(int i = 0; i < stack.size; i++)
    {
        items[i] = stack.items[i];
    }   
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& stack)
{
    if(this != &stack)
    {
        if(!stack.isEmpty())
        {
          clear();
          for(int i = 0; i < stack.size; i++)
          {
            push(stack.items[i]);
          }
        }
        else
        {
          size = 0;
          delete [] items;
          capacity = stack.capacity;
          items = new T[capacity];
        }
    }
    return *this;
}

template <class T>
Stack<T>::~Stack()
{
    delete [] items;
}

template <class T>
void Stack<T>::push(const T& item)
{
    if(size == capacity)
    {
        T* newitems = new T[capacity*2];
        for(int i = 0; i < size; i++)
        {
           newitems[i] = items[i];
        }
        newitems[size] = item;
        delete [] items;
        items = newitems;
        capacity *= 2;
    }
    else
    {
        items[size] = item;
    }
    size++;
}

template <class T>
T Stack<T>::pop()
{
   if(isEmpty())
   {
      throw runtime_error("empty stack");
   }
   else
   {
       T* newitems;
       T toBePopped = items[size-1];
       if(size * 3 < capacity && capacity >= 16)
       {
          newitems = new T[capacity/2];
          capacity /= 2;
       }
       else
       {
          newitems = new T[capacity];
       }
       for(int i = 0; i < size - 1; i++)
       {
          newitems[i] = items[i];
       }
       delete [] items;
       items = newitems;
       size--;
       return toBePopped;
   }   
}

template <class T>
const T& Stack<T>::top() const
{
   if(isEmpty())
   {
      throw runtime_error("empty stack");
   } 
   else return items[size-1];
}

template <class T>
void Stack<T>::clear()
{
    if(!isEmpty())
    {
        delete [] items;
        items = new T[8];
        size = 0;
        capacity = 8;
    }
}

template <class T>
bool Stack<T>::isEmpty() const
{
    return size == 0;
}

template <class T>
size_t Stack<T>::getSize() const
{
    return size;
}

template <class T>
size_t Stack<T>::getCapacity() const
{
    return capacity;
}

template <class T>
void Stack<T>::print() const
{
  if(!isEmpty())
  {
     int i = size - 1;
     while(i)
     {
        cout << items[i] << endl;
        i--;
     }
     cout << items[0] << endl;  
  }    
}

template <class T>
void Stack<T>::printReversed() const
{
  if(!isEmpty())
  {
      int i = 0;
      while(i < size)
      {
        cout << items[i] << endl;
        i++;
      }   
  } 
}
#endif