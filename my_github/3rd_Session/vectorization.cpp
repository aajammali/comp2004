/*
------------------DR VASILIOS KELEFOURAS-----------------------------------------------------
------------------COMP2004 ------------------------------------------------------------------
------------------EMBEDDED PROGRAMMING AND THE INTERNET OF THINGS-------------------------------------------------
------------------UNIVERSITY OF PLYMOUTH, SCHOOL OF ENGINEERING, COMPUTING AND MATHEMATICS---
*/


#include "mbed.h"
#include "string.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

//Serial Interface
//Serial pc(USBTX, USBRX);

Timer timer;

#define NN 8000
#define N 90

uint8_t in[NN], out[NN], out2[NN]; //unit8_t is a data type for unsigned integers of 8-bit
int16_t inp[N][N],X[N]; //int16_t is for 16-bit signed integers
int32_t outp[N],outp2[N];



void initialization();
void exerc1();
void exerc2();
void exerc3();
void exerc4();

// Main program function.
int main() {
  
	
printf("\n\r Programmed started \n\r");

	initialization();
	
	printf("\n\rTimer started!\n");
	timer.start();
    
//FOUR DIFFERENT EXAMPLES ARE PROVIDED ON HOW TO USE VECTORIZATION ON THE NUCLEO BOARD 
//--------------------------------
	exerc1();
	//exerc2();
	//exerc3();
	//exerc4();
//------------------------------------------------------------------------------
    timer.stop();
    printf("\n\rThe time taken for the routine was %f seconds\n", timer.read());


  return 0;
}




void initialization(){
	int i,j;
	
//This is a greyscale image with random values
	for (i=0;i<N;i++)
	 for (j=0;j<N;j++)
	  inp[i][j]=rand()%255;
	/*
		for (i=0;i<N;i++){printf(" \n\r");
	   for (j=0;j<M;j++){
			 printf(" %d",inp_img[i][j]);
		 }}
	*/
	   for (j=0;j<N;j++){
	    outp[j]=0;
	    outp2[j]=0;
		 }
	
		 
		 	for (i=0;i<N;i++){
				out[i]=0;
				out2[i]=0;
				in[i]=-1*(rand()%255);
				X[i]=rand()%65536;
			}
}


void exerc1(){
	
	int32_t temp;
	uint32_t t,u;
	
	//default loop kernel (un-optimized)
	for (int i=0; i<NN; i++){
		temp=in[i]-100;
		if (temp<0)
			temp=0;
		
		out[i]=(uint8_t) temp;
		
	}
	
	//--------------------

	//vectorized loop kernel (optimized)
	for (int i=0; i<NN; i+=4){

	t=* ((uint32_t *) &in[i]);
	u = __UQSUB8(t,0x64646464);//100 in decimal is 64 in hexadecimal. the 0x means hexadecimal number follows
	* ((uint32_t *) &out2[i])=u;
		
	}
		
	//this is just to compare the results of the un-optimized loop kernel with the results of the optimized one
	for (int i=0; i<NN; i++){
	 if (out[i]!=out2[i])
    	  printf("\n\r\n\r %d %d %d",in[i],out[i],out2[i]);	
	}	
	
		
}


void exerc2(){
	
	uint32_t t,u;
	int32_t temp;
	
	//default loop kernel (un-optimized)
	for (int i=0; i<NN; i++){
		temp=(in[i]+100);
  	out[i]=(uint8_t) temp;
	}
	
	//vectorized loop kernel (optimized)
	for (int i=0; i<NN; i+=4){

	t=* ((uint32_t *) &in[i]);
	u = __UADD8(t,0x64646464);//100 in decimal is 64 in hexadecimal. the 0x means hexadecimal number follows
	* ((uint32_t *) &out2[i])=u;
		
	}
	
	//this is just to compare the results of the un-optimized loop kernel with the results of the optimized one
	for (int i=0; i<NN; i++){
	 if (out[i]!=out2[i])
    	  printf("\n\r\n\r %d -- %d %d %d",i, in[i],out[i],out2[i]);	
	}
	

	
}

void exerc3(){
	
	uint32_t t,u;
	int32_t temp;
	
	//default loop kernel (un-optimized)
	for (int i=0; i<NN; i++){
		out[i]=(in[i]+100)/2;
	}
	
	//vectorized loop kernel (optimized)
	for (int i=0; i<NN; i+=4){

	t=* ((uint32_t *) &in[i]);
	u = __UHADD8(t,0x64646464);//100 in decimal is 64 in hexadecimal. the 0x means hexadecimal number follows
	* ((uint32_t *) &out2[i])=u;
		
	}
	
	//this is just to compare the results of the un-optimized loop kernel with the results of the optimized one
	for (int i=0; i<NN; i++){
	 if (out[i]!=out2[i])
          printf("\n\r\n\r %d -- %d %d %d",i, in[i],out[i],out2[i]);	
	}
	
}

void exerc4(){
	
	uint32_t t,u;
	int32_t r0,r1,r2,r3,y0,y1,y2,y3,y4,y5,y6,y7,y8,y9,y10,x0,a0;
	int i,j;
	
	//default loop kernel (un-optimized) - 16-bit inputs, 32-bit output
	for (i=0;i<N;i++)
	  for (j=0;j<N;j++){
			outp[i]+=inp[i][j]*X[j];
		}

	//vectorized loop kernel (optimized version1) - 16-bit inputs, 32-bit output
	for (i = 0; i < N; i++) {
		r2 = 0;
		for (j = 0; j < N; j += 2) {
			r0 = *((uint32_t*)&inp[i][j]);
			r1 = *((uint32_t*)&X[j]);
			r2 = __smlad(r0, r1, r2);
		}
		outp2[i] = r2;
	}


	//	//vectorized loop kernel (optimized version2) - vectorization + register blocking
	for (i=0;i<N;i+=9){
		y0=0; y1=0; y2=0; y3=0; y4=0; y5=0; y6=0; y7=0; y8=0; 
	  for (j=0;j<N;j+=2){
		 x0=* ((uint32_t *) &X[j]);
			
		 a0=* ((uint32_t *) &inp[i][j]);
		 y0 = __smlad(a0,x0,y0);
		 a0=* ((uint32_t *) &inp[i+1][j]);
		 y1 = __smlad(a0,x0,y1);
		 a0=* ((uint32_t *) &inp[i+2][j]);
		 y2 = __smlad(a0,x0,y2);
		 a0=* ((uint32_t *) &inp[i+3][j]);
		 y3 = __smlad(a0,x0,y3);
		 a0=* ((uint32_t *) &inp[i+4][j]);
		 y4 = __smlad(a0,x0,y4);
		 a0=* ((uint32_t *) &inp[i+5][j]);
		 y5 = __smlad(a0,x0,y5);
		 a0=* ((uint32_t *) &inp[i+6][j]);
		 y6 = __smlad(a0,x0,y6);
		 a0=* ((uint32_t *) &inp[i+7][j]);
		 y7 = __smlad(a0,x0,y7);			
		 a0=* ((uint32_t *) &inp[i+8][j]);
		 y8 = __smlad(a0,x0,y8);	
		}
		outp2[i]=y0;
		outp2[i+1]=y1;
		outp2[i+2]=y2;
		outp2[i+3]=y3;
		outp2[i+4]=y4;
		outp2[i+5]=y5;
		outp2[i+6]=y6;
		outp2[i+7]=y7;
    outp2[i+8]=y8;
	}
	
	/*	
	//this is just to compare the results of the un-optimized loop kernel with the results of the optimized one
	for (int i=0; i<N; i++){
		if (outp[i]!=outp2[i])
     printf("\n\r\n\r %d -- %d %d",i, outp[i],outp2[i]);	
	}
		*/
		 
}



