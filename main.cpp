#include "simulation.h"

int main(int argc, char **argv){

  simulation newSimulation;

  if(argc > 1){
    // set the file name equal to the arg
    string inputFileName = argv[1];
    cout << "Input file name taken in by command line input." << endl;
    string infoReport = newSimulation.studentWindows(inputFileName);
  }
  else{
    cout << "Error: you did not enter the name of the file to read." << endl;
  }

  return 0;
}
