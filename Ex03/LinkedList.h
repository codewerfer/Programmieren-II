#pragma once
#include <cstddef>

/**
 * \brief class LinkedList
 * 
 * (ASCII explanation longer than 80 chars)
 *
 * *first --> |  Node  |          |  Node  |            |  Node  | <-- *last
 *            | T data | -*next-> | T data | -- ... --> | T data | -*next-> NULL
 * 
 * Insert => O(1) (at the end)
 * begin  => O(1)
 * Random access => O(n) (via begin()->next->next...)
 * \tparam T Type of LinkedList elements
 */
template <class T>
class LinkedList
{
public:

  /**
   * \brief Node structure
   * contains T data and a link to the next Node, NULL if it doesn't exists
   */
  struct Node
  {
    T data; /// data of type T
    Node* next; /// next Node, NULL if it doesn't exists
    explicit Node(T t) : data(t) { next = NULL; } /// constructor
  };


  /**
   * \brief Constructor of LinkedList, sets first an last to NULL
   */
  LinkedList();

  /**
   * \brief Deconstructor, clears the LinkedList - frees all Nodes
   */
  ~LinkedList()
  {
    clear();
  }

  /**
     * \brief Access to elements, Node per Node.
     * begin()->data gives first data element of type T.
     * Iterate with begin()->next->next->..
     * \return Read only pointer to first Node.
     */
  const Node* begin() const { return first; }

  /**
   * \brief Clears LinkedList, deletes all Nodes
   */
  void clear();

  /**
   * \brief Adds element t at the end of the list.
   * \param t Element of type T
   */
  void insert(T t);

private:
  Node* first;
  Node* last;
};
