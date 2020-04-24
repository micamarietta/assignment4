#include <iostream>

template<typename t>
class List{
public:
  t data;
  List *next;
  List *prev;

  List(){
    next = NULL;
  }

  List(t d){
    data = d;
    next = NULL;
  }

  ~List(){
    next = NULL;
    delete next;
  }
};
