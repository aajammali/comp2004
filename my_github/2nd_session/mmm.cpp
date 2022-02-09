/*
------------------DR VASILIOS KELEFOURAS-----------------------------------------------------
------------------COMP2004 ------------------------------------------------------------------
------------------EMBEDDED PROGRAMMING AND THE INTERNET OF THINGS-------------------------------------------------
------------------UNIVERSITY OF PLYMOUTH, SCHOOL OF ENGINEERING, COMPUTING AND MATHEMATICS---
*/

//apply register blocking to j loop with a factor of 2,4,8,10,16
//apply register blocking to i loop with a factor of 2,4,8,10,16
//apply register blocking to both i and j loop with a factor of 2,4

#include "mbed.h"

void initialize();
void mmm();
void mmm_reg_blocking_4();
void mmm_reg_blocking_8();


Timer t;
#define N 80

float A[N][N], B[N][N], C[N][N];

using namespace std::chrono;
// main() runs in its own thread in the OS


int main()
{
    int i,j,k;

    printf("Hello \n");

initialize();

t.reset();    
t.start();

   

  mmm();


t.stop();
//printf("\nThe time taken was %f secs\n",t.read());
printf("\nThe time taken was %llu msecs\n",duration_cast<milliseconds>(t.elapsed_time()).count());

return 0;
}


void initialize(){

int i,j;

for (i=0;i<N;i++)
 for (j=0;j<N;j++){
  A[i][j]=(float) (j%99 + 0.1);
  B[i][j]=(float) (j%65 - 0.1);
  C[i][j]=0.0;

}

}

void mmm(){

int i,j,k;

for (i=0;i<N;i++)
 for (j=0;j<N;j++)
  for (k=0;k<N;k++) 
 C[i][j]+=A[i][k]*B[k][j];
 

}





//assume that N%4==0
void mmm_reg_blocking_4(){

int i,j,k;
float c0,c1,c2,c3,a;

//register blocking has been applied to j loop by a factor of 4.
for (i=0;i<N;i++)
 for (j=0;j<N;j+=4){
 c0=C[i][j];
 c1=C[i][j+1];
 c2=C[i][j+2];
 c3=C[i][j+3];
  for (k=0;k<N;k++) {
 a=A[i][k];
 c0+=a*B[k][j];
 c1+=a*B[k][j+1];
 c2+=a*B[k][j+2];
 c3+=a*B[k][j+3];
}
C[i][j]=c0;
C[i][j+1]=c1;
C[i][j+2]=c2;
C[i][j+3]=c3;
}


}


//assume that N%8==0
void mmm_reg_blocking_8(){

int i,j,k;
float c0,c1,c2,c3,c4,c5,c6,c7,c8,a;

//register blocking has been applied to j loop by a factor of 4.
for (i=0;i<N;i++)
 for (j=0;j<N;j+=8){
 c0=C[i][j];
 c1=C[i][j+1];
 c2=C[i][j+2];
 c3=C[i][j+3];
 c4=C[i][j+4];
 c5=C[i][j+5];
 c6=C[i][j+6];
 c7=C[i][j+7];
  for (k=0;k<N;k++) {
 a=A[i][k];
 c0+=a*B[k][j];
 c1+=a*B[k][j+1];
 c2+=a*B[k][j+2];
 c3+=a*B[k][j+3];
 c0+=a*B[k][j+4];
 c1+=a*B[k][j+5];
 c2+=a*B[k][j+6];
 c3+=a*B[k][j+7];
}
C[i][j]=c0;
C[i][j+1]=c1;
C[i][j+2]=c2;
C[i][j+3]=c3;
C[i][j+4]=c4;
C[i][j+5]=c5;
C[i][j+6]=c6;
C[i][j+7]=c7;
}


}
