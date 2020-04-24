#include "student.h"

student::student(){
  //nada
}

student::student(int tim, int duration){
  m_timeinQueue = tim;
  m_duration = duration;
}

student::~student(){
  //nada
}

void student::settimeinQueue(int timeinQueue){
  m_timeinQueue = timeinQueue;
}

int student::gettimeinQueue(){
  return m_timeinQueue;
}

void student::setDuration(int duration){
  m_duration = duration;
}

int student::getDuration(){
  return m_duration;
}

void student::setWaitTime(int waitTime){
  m_waitTime = waitTime;
}

int student::getWaitTime(){
  return m_waitTime;
}

void student::setTimeinWindow(int timeinWindow){
  m_timeinWindow = timeinWindow;
}

int student::getTimeinWindow(){
  return m_timeinWindow;
}

void student::setTimeoutWindow(int timeoutWindow){
  m_timeoutWindow = timeoutWindow;
}

int student::getTimeoutWindow(){
  return m_timeoutWindow;
}

void student::setName(string name){
  m_name = name;
}

string student::getName(){
  return m_name;
}


bool student::shouldLeave(int timeTick){
  return (m_duration + m_timeinWindow - m_waitTime <= timeTick);
}
