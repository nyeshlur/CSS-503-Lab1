/*
Lab 1, completed by Nayana Yeshlur and Jenny Wilson.
Starter code provided by Professor Dimpsey.

g++ -g -std=c++11 -o myprog lab1.cpp
./myprog
*/

#include <iostream>    // cout, cerr 
#include <queue>       // stl queue 
#include <sys/types.h> // fork, wait 
#include <sys/wait.h>  // wait 
#include <unistd.h>    // fork 
#include <stdlib.h> // for exit


using namespace std; 


queue<int> pids;      // stores a list of processes from the parent to a leaf process

void recursive_creation(int leaves) 
{
    if (leaves > 1)
    { 
        int subLeaves;
        subLeaves = leaves / 2;
        pids.push(getpid()); 
        int status;
        int leftPID = fork(); // fork a left child 
        if(leftPID == 0) { //if you are in the child process
            subLeaves = subLeaves + (leaves % 2);
            recursive_creation(subLeaves);
        } else { //if you are in the parent process
            wait(&status);
            int rightPID = fork(); // fork a right child
            if(rightPID == 0) {
                recursive_creation(subLeaves);
            } else {
                wait(&status);
            }
        }

        exit(0); 

    } else
   { // I'm a leaf process 
       while(pids.size() > 0)
       {  // print out a list of my ascendants 
           cout << pids.front() << " "; 
           pids.pop( ); 
       } 

       cout << getpid() << endl;   // print out myself 
       exit(0); 

   }
}

int main(int argc, char* argv[])
{

   // validate arguments 
   if (argc != 2)

   { 
       cerr << "usage: lab1 #leaves" << endl; 
       return -1; 
   } 
   int leaves = atoi(argv[1]); 
   if ( leaves < 1 )

   { 
      cerr << "usage: lab1 #leaves" << endl; 
      cerr << "where #leaves >= 1" << endl; 
      return -1; 
   } 
    recursive_creation(leaves); 
   return 0;
   
}
