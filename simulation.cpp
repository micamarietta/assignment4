#include <iostream>
#include "simulation.h"
#include <iostream>
#include <fstream>
#include "student.h"
#include <algorithm>
using namespace std;

simulation::simulation(){
  //nothing
}

string simulation::studentWindows(string file){
  ifstream inFS;
  string currentLine;
  int lineNumber = 1;
  int numOfStudents;
  int windowNumber;
  int prevTime = 0;
  int duration;
  string names[10] = {"Mica", "Nick", "Matt", "Ryan", "Kacey", "Maggie", "Kona", "Jaxon", "Jane", "Mark"};
  student dummyStudent;
  dummyStudent.setName("Dummy");

//for calculations
  double meanWaitTime;
  double medianWaitTime;
  int longestWaitTime;
  int studentsWaitingOverTen = 0;
  int meanWindowIdleTime = 0;
  int longestWindowIdleTime = 0;
  int windowsIdleOverFive = 0;
  int totalStudents = 0;

  //make the queue of students that will be filled after reading the file
  queue<student> *students = new queue<student>(1);

  //read from the file
  inFS.open(file);

  //indicate that the file has been opened
  if(inFS.is_open()){
    cout << "File has been opened" << endl;
  }

  //follow the pattern in order to get the proper variables: num windows open, time, num students, time each student needs

  //get number of windows
  getline(inFS, currentLine);
  windowNumber = stoi(currentLine);
  cout << "there are " << windowNumber << " windows open" << endl;
  student windows[windowNumber];
  int windowWaitTimes[windowNumber];
  student allStudents[30];
  for(int i = 0; i < windowNumber ; ++i){
    windows[i] = dummyStudent;
    windowWaitTimes[i] = 0;
  }

  while(getline(inFS, currentLine)){
    int currTime = stoi(currentLine);
    cout << "===================================================" << endl;
    cout << "TICK: " << currTime << endl;

    //get the number of students for that time
    getline(inFS, currentLine);
    numOfStudents = stoi(currentLine);
    cout << "there are " << numOfStudents << " students" << endl;

    //loop through students, add them to queue, record time arrived and duration
    for (int i = 1; i<= numOfStudents; ++i){
      getline(inFS, currentLine);
      duration = stoi(currentLine);
      student *stu = new student(currTime, duration);
      stu->setName(names[totalStudents]);
      students->insert(*stu);

      cout << "student " << stu->getName() << " (" << totalStudents << ") has arrived and will be here for " << duration << endl;

      // add the student to the allStudents array
      allStudents[totalStudents] = *stu;
      totalStudents++;
    }

    //check if windows are open and see if students have reached their duration
    for(int i = 0; i < windowNumber; ++i){
      //if there is someone in the window, check if they need to get kicked out
      if(windows[i].getName() != "Dummy"){
        if(windows[i].shouldLeave(currTime)){

          //if they leave, record time they left the room
          windows[i].setTimeoutWindow(currTime);
          windows[i] = dummyStudent;
          cout << "window " << i << " is now empty, student " << windows[i].getName() << " has left" << endl;
        }else{
          cout << "window " << i << " has student " << windows[i].getName() << endl;
        }
      } else{
        cout << "window " << i << " is empty " << endl;
        //windowWaitTimes[i]++;
      }
    }

    //fill any empty windows with students from the q
    for(int i = 0; i < windowNumber; ++i){
      if(windows[i].getName() == "Dummy" && !students->isEmpty()){

        //the window is empty, pop the student from the q
        student stud = students->remove();
        cout << "student  " << stud.getName() << " has been removed from the queue and put into window " << i << endl;

        //put student into the window
        windows[i] = stud;
      }
    }

    for(int i = 0; i < windowNumber; ++i){
      if(windows[i].getName() == "Dummy"){
        cout << "incrementing wait time for window " << i << endl;
        windowWaitTimes[i] = windowWaitTimes[i] + (currTime - prevTime);
      }
    }

    // increment the wait time for any students remaining in queue
    if (!students->isEmpty()){
      for(int i = 0; i < students->getSize(); ++i){
        student stu = students->accessElement(i);
        int curWaitTime = stu.getWaitTime();
        stu.setWaitTime(curWaitTime + 1);
        cout << "the wait time was updated to " << stu.getWaitTime() << endl;
      }
    }

    prevTime = currTime;
  }

  cout << "===================================================" << endl;
  cout << "Total Students: " << totalStudents << endl;

  //make calculations based on simulation

  //calc mean wait time
  double temp = 0;
  for(int i = 0; i < totalStudents; ++i){
    temp = temp + (allStudents[i].getWaitTime());
    cout << "student " << allStudents[i].getName() <<" has been waiting " << allStudents[i].getWaitTime() << endl;
  }
  meanWaitTime = temp / totalStudents;

  //median wait time for students
  int studentWaitTimes[totalStudents];
  int swtSorted[totalStudents];

  for(int i = 0; i < totalStudents; ++i){
    studentWaitTimes[i] = allStudents[i].getWaitTime();
  }

  sort(studentWaitTimes, studentWaitTimes + 1);

  medianWaitTime = studentWaitTimes[totalStudents / 2];


  //longest wait time
  int max = allStudents[0].getWaitTime();
  for(int i = 0; i < totalStudents; ++i){
    if(max < allStudents[i].getWaitTime()){
      max = allStudents[i].getWaitTime();
    }
    longestWaitTime = max;
  }

  //number of students waiting over ten minutes
  for(int i = 0; i < totalStudents; ++i){
    if(allStudents[i].getWaitTime() > 10){
      studentsWaitingOverTen++;
    }
  }

  //mean window idle time
  for(int i = 0; i < windowNumber; ++i){
    meanWindowIdleTime = meanWindowIdleTime + windowWaitTimes[i];
  }
  meanWindowIdleTime = meanWindowIdleTime / windowNumber;

  //longest window idle time
  longestWindowIdleTime = windowWaitTimes[0];
  for(int i = 0; i < windowNumber; ++i){
    if(windowWaitTimes[i] > longestWindowIdleTime){
      longestWindowIdleTime = windowWaitTimes[i];
    }
  }

  //num of windows idle for over five minutes
  for(int i = 0; i < windowNumber; ++i){
    if(windowWaitTimes[i] > 5){
      windowsIdleOverFive++;
    }
  }

  cout << "Registrar Simulation Statistics: " << endl;
  cout << "Mean student wait time : " << meanWaitTime << endl;
  cout << "Median student wait time : " << medianWaitTime << endl;
  cout << "Longest student wait time : " << longestWaitTime << endl;
  cout << "Number of students waiting over 10 minutes : " << studentsWaitingOverTen << endl;
  cout << "Mean window idle time : " << meanWindowIdleTime << endl;
  cout << "Longest window idle time : " << longestWindowIdleTime << endl;
  cout << "Number of windows idle for over 5 minutes : " << windowsIdleOverFive << endl;

}
