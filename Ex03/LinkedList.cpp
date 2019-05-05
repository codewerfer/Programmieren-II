// ---------------------------------------------------------
// LinkedList.cpp
// Source file for class LinkedList<T>
//
// Author: Jürgen Vogl <k1355432>
// Last Modification: 05.05.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------
#include "LinkedList.h"

template <class T>
inline LinkedList<T>::LinkedList()
{
  first = last = NULL;
}

template <class T>
inline void LinkedList<T>::clear()
{
  Node* next = first;
  while (next)
  {
    Node* remove = next;
    next = next->next;
    delete remove;
  }
  first = last = NULL;
}

template <class T>
inline void LinkedList<T>::insert(T t)
{
  Node* n = new Node(t);
  if (!first)
  {
    first = last = n;
  }
  else
  {
    last->next = n;
    last = last->next;
  }
}
