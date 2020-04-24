#ifndef _DOUBLYLINKEDLIST_HPP_
#define _DOUBLYLINKEDLIST_HPP_

#include <iostream>
#include "List.hpp"
#include "student.h"
using namespace std;

template<typename t>
class DoublyLinkedList{

public:
  List<t> *front;
  unsigned int size;
  List<t> *back;

  DoublyLinkedList(){
    size = 0;
    front = NULL;
    back = NULL;
  }

  ~DoublyLinkedList(){
    front = NULL;
    back = NULL;
    delete front;
  }

  virtual unsigned int getSize(){
    return size;
  }

  virtual t accessData(int pos){
    int idx = 0;
    List<t> *curr = front;
    List<t> *prev = front;

    while(idx != pos){
      //loop until i find the position
      prev = curr;
      curr = curr->next;
      idx++;
    }

    //now let's continue with the deletion process
    return curr->data;
  }

  virtual bool isEmpty(){
    return (size==0);
  }

  virtual void printList(){
    List<t> *curr = front;
    while(curr != NULL){
      cout << curr->data.getName() << endl;
      curr = curr->next;
    }
  }

  virtual void insertFront(t d){
    List<t> *node = new List<t>();
    // node->data = d;

    if(isEmpty()){
      back = node;

    } else{
      //not empty
      front->prev = node;
      node->next = front;
    }
    front = node;
    size++;
  }

  virtual void insertBack(t d){
    List<t> *node = new List<t>();
    node->data = d;

    if(isEmpty()){
      front = node;

    } else{
      //not empty
      back->next = node;
      back->prev = back;
    }
    back = node;
    cout << "student being added is " << d.getName() << endl;
    size++;
  }

  virtual t removeFront(){
    //check if empty before removing
    if(size ==1){
      //t temp = front->data;
      student student = front->data;
      cout << " (remove front) name is " << student.getName() << endl;
      List<t> *ft = front;
      front = NULL;
      delete ft;
      size--;
      return student;
    }
    //t temp = front->data;
    student student = front->data;
    cout << "(remove front) name is " << student.getName() << endl;
    List<t> *ft = front;
    front = front->next;
    front->prev = NULL; //added
    ft->next = NULL;
    delete ft;
    size--;
    return student;
  }

  virtual int search(t obj){
    int pos = -1;
    List<t> *curr = front;
    //let's loop and attempt to find the value
    while(curr != NULL){
      ++pos;
      //if(curr->data = obj){
        //we found it
        //break;
      }
    //   {
    //     //we didn't find it
    //     curr = curr->next;
    //   }
    //
    //   if(curr = NULL){
    //     //we didn't find it at all within the list
    //     pos = -1;
    //   }
    //   return pos;
    // }
  }

  virtual void removeAtPos(int pos){
    //error to make sure pos does not exceed size of list
    int idx = 0;
    List<t> *curr = front;
    List<t> *prev = front;

    while(idx != pos){
      //loop until i find the position
      prev = curr;
      curr = curr->next;
      idx++;
    }

    //now let's continue with the deletion process
    prev->next = curr->next;
    curr->next = NULL;
    t temp = curr->data;
    delete curr;
    size--;

    //return temp;
  }

  virtual void remove(t obj){
    //need to find the value in the list before we can delete
    //this function does not take in a position as a parameter
    List<t> *curr = front;

    //lets look for this value
    //while(curr-> data != obj){
      //curr = curr->next;

      //if(curr == NULL){
      //  return -1;
      //}
    //}

    //if we get here, we found our node/value, now let's proceed to delete
    if(curr == front){
      //if node to be deleted is at the front
      front = curr->next;
    }
    else{
      //node to be deleted is somewhere in between front and back
      curr->prev->next = curr->next;
    }

    if(curr == back){
      back = curr->prev;
    }
    else{
      //node to be deleted is somewhere in between front and back
      curr->next->prev = curr->prev;
    }

    //can break it up into if it is front, else if back, and else in the middle
    curr->next = NULL;
    curr->prev = NULL;
    t temp = curr->data;
    size--;
    delete curr;

    //return temp;

  }
private:
};

#endif
