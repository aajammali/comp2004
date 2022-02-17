/*
------------------DR VASILIOS KELEFOURAS-----------------------------------------------------
------------------COMP2004 ------------------------------------------------------------------
------------------EMBEDDED PROGRAMMING AND THE INTERNET OF THINGS-------------------------------------------------
------------------UNIVERSITY OF PLYMOUTH, SCHOOL OF ENGINEERING, COMPUTING AND MATHEMATICS---
*/

#include "mbed.h"
Timer t;
#define N 100

double A[N][N];
//double table[7]={1.414213562373, 1.732050807569, 2.0, 2.236067977500,2.449489742783, 2.645751311065, 2.828427124746};

using namespace std::chrono;
// main() runs in its own thread in the OS


int main()
{
    int i,j,k;

    printf("Hello \n");


t.reset();    
t.start();

    for (i=0; i<N; i++)  { 
        for (j=0;j<N;j++){
            A[i][j]=0.0;
          for (k=2;k<9;k++){
              A[i][j]+=i*sqrt((double) k) + j*sqrt((double) k);
             // A[i][j]+=i*table[k-2] + j*table[k-2];
          }
        }
    }

t.stop();
//printf("\nThe time taken was %f secs\n",t.read());
printf("\nThe time taken was %llu msecs\n",duration_cast<milliseconds>(t.elapsed_time()).count());

return 0;
}

