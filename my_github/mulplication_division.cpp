/*
------------------DR VASILIOS KELEFOURAS-----------------------------------------------------
------------------COMP2004 ------------------------------------------------------------------
------------------EMBEDDED PROGRAMMING AND THE INTERNET OF THINGS-------------------------------------------------
------------------UNIVERSITY OF PLYMOUTH, SCHOOL OF ENGINEERING, COMPUTING AND MATHEMATICS---
*/

#include "mbed.h"
Timer t;
#define N 100
using namespace std::chrono;
// main() runs in its own thread in the OS

float A[N][N];

int main()
{
    int i,j,times;
    printf("Hello \n");

    for (i=0; i<N; i++) 
    {
        for (j=0;j<N;j++)
        A[i][j]=(float) (j+0.1);
    }
t.reset();    
t.start();

for (times=0;times<100;times++)//run many times the following code as otherwise the ex.time is tiny
    for (i=0; i<N; i++) 
    {
        for (j=0;j<N;j++)
        A[i][j]=A[i][j]/5.0f;
	//A[i][j]=A[i][j]*0.2f;
        //printf(" %d",A[i][j]);
    }

t.stop();
//printf("\nThe time taken was %f secs\n",t.read());
printf("\nThe time taken was %llu msecs\n",duration_cast<milliseconds>(t.elapsed_time()).count());

return 0;
}
