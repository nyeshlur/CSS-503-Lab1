/*
Lab 1, completed by Nayana Yeshlur and Jenny Wilson.
Starter code provided by Professor Dimpsey.
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
    int leftStatus, rightStatus;
    if (leaves > 1)

   { 
        pids.push(getpid()); 

        int leftPID = fork(); // fork a left child 
        cout << "got here" << endl;
        wait(&leftStatus);
        recursive_creation(leaves - 1);

       // int rightPID = fork(); // fork a right child
        //wait(&rightStatus);
        
        /*
        int rightPID = fork(); // fork a right child 
        //pids.push(rightPID);
        recursive_creation(leaves - 1);
        wait(&rightStatus);
        */

       

        exit(0); 

   } 
   else
   { // I'm a leaf process 
       while(pids.size() > 0)
       {  // print out a list of my ascendants 
       cout << "got there" << endl;
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
