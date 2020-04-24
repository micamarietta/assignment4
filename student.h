#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <iostream>
#include <string>

using namespace std;

class student{
private:
  int m_timeinQueue;
  int m_duration;
  int m_waitTime;
  int m_timeinWindow;
  int m_timeoutWindow;
  string m_name;

public:
  student();
  student(int tim, int duration);
  ~student();
  void settimeinQueue(int timeinQueue);
  int gettimeinQueue();
  void setDuration(int duration);
  int getDuration();
  void setWaitTime(int waitTime);
  int getWaitTime();
  void setTimeinWindow(int timeinWindow);
  int getTimeinWindow();
  void setTimeoutWindow(int timeoutWindow);
  int getTimeoutWindow();
  void setName(string name);
  string getName();

  bool shouldLeave(int timeTick);
};

#endif
