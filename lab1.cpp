#include <iostream>    // cout, cerr 
#include <queue>       // stl queue 
#include <sys/types.h> // fork, wait 
#include <sys/wait.h>  // wait 
#include <unistd.h>    // fork 
#include <stdlib.h>    // for exit  

using namespace std; 
 
queue<int> pids;      // stores a list of processes from the parent to a leaf process

void recursive_creation(int leaves)
{
    if (leaves > 1)     //if there is more than just the root, go into IF
    { 
        int status, leftChild, rightChild;
        int children = leaves / 2;  //half the children go on each side
        pids.push(getpid());        //push the pid of the current process

        // fork a left child because if leaves > 1 there is always *at least* one left child
        leftChild = fork();
        if (leftChild == 0)  {          //inside the left child
            children += (leaves % 2);   //determine if there is an odd leaf. This adds either 1 or 0
                                        //children is the number of leaves this root (leftChild) will have
            recursive_creation(children);
        } else                      //not in the left child
        {
            wait(&status);          //wait for leftChild to finish its process
            rightChild = fork();    //fork the right child
            if (rightChild == 0)    //inside the right child
            {
                recursive_creation(children);
            } else
            {
                wait(&status);      //wait for a child
            }
        }

   } 
   else
    { // I'm a leaf process 
   // cout << "printing pids" << endl;
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