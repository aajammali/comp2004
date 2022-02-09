/*
------------------DR VASILIOS KELEFOURAS-----------------------------------------------------
------------------COMP2004 ------------------------------------------------------------------
------------------EMBEDDED PROGRAMMING AND THE INTERNET OF THINGS-------------------------------------------------
------------------UNIVERSITY OF PLYMOUTH, SCHOOL OF ENGINEERING, COMPUTING AND MATHEMATICS---
*/


#include <stdio.h>
#include <time.h>
#include <pmmintrin.h>
#include <process.h>
#include <chrono>
#include <iostream>

#define M 8096


int B[M][M];

int main() {

	clock_t start_1, end_1;

	//start_1 = clock();
	auto start = std::chrono::high_resolution_clock::now();

	
	//row-wise initialization
	for (int i = 0; i != M; i++)
		for (int j = 0; j != M; j++)
			B[i][j] = i + j;
			

	//column-wise initialization
	/*
    for (int j = 0; j != M; j++)
		for (int i = 0; i != M; i++)
			B[i][j] = i + j;
	*/
	

	auto finish = std::chrono::high_resolution_clock::now();
	//end_1 = clock();

	//printf(" clock() method: %ldms\n", (end_1 - start_1) / (CLOCKS_PER_SEC / 1000));
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";

	system("pause");
	return 0;
}
