#include <iostream>
#include "DoublyLinkedList.hpp"
using namespace std;

template<typename t>
class queue{
public:
  queue(){
    //nothing yet
  }

  queue(int maxSize){
    list = new DoublyLinkedList<t>[maxSize];
    mSize = maxSize;
    front = 0;
    rear = -1;
    numElements = 0;
  }

  ~queue(){
    delete list;
  }

  void insert(t data){
    list->insertBack(data);
    cout << "here is the queue : " << endl;
    list->printList();
    ++numElements;
  }

  t accessElement(int i){
    return list->accessData(i);
  }

  t remove(){
    //error checking
    //cout << "getting to line before enters DLL" << endl;
    --numElements;
    return list->removeFront();
  }

  t peek(){
    return list->front->data;
  }

  bool isFull(){
    return (numElements == mSize);
  }

  bool isEmpty(){
    return (numElements == 0);
  }

  int getSize(){
    return numElements;
  }

  //vars
  int front;//aka head
  int rear; //aka tail
  int mSize;
  int numElements;

  char *myQueue; //array

private:
  DoublyLinkedList<t> *list;
};
