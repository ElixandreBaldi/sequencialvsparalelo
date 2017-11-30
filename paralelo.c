#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"

#define M 14750
#define N 2

double matrixA[M][M];
double matrixB[M][M];
double results = 0;
void printMatrixAB(){
	for(int i = 0; i < M; i++){
		for(int j = 0; j < M; j++){
			printf("%lf \t",matrixA[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
	for(int i = 0; i < M; i++){
		for(int j = 0; j < M; j++){
			printf("%lf \t",matrixB[i][j]);
		}
		printf("\n");
	}
}

void printMatrixDR(){
	printf("\n");
	printf("\n");
	for(int i = 0; i < M; i++){
		for(int j = 0; j < M; j++){
			printf("%lf \t",matrixB[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("results: %lf\n",results);
}

void genareteSquare(){
	int i, j;
	#pragma omp parallel shared(i, matrixA, matrixB) private(j)
	{	
		#pragma omp for
		for(i = 0; i < M; i++){
			for(j = 0; j < M; j++){
				matrixA[i][j] = matrixA[i][j]*matrixA[i][j];
				matrixB[i][j] = matrixB[i][j]*matrixB[i][j];
			}	
		}		
	}
}

void genareteDiferents(){
	int i, j;
	#pragma omp parallel shared(i, matrixA, matrixB) private(j)
	{
		#pragma omp for
		for(i = 0; i < M; i++){
			for(j = 0; j < M; j++){
				matrixB[i][j] = matrixA[i][j] - matrixB[i][j];
			}	
		}		
	}
}

void genareteSum(){
	int i, j;
	#pragma omp parallel shared(i, results, matrixB) private(j)	
	{
		#pragma omp for 
		for(i = 0; i < M; i++){		
			double resultParcial = 0;
			for(j = 0; j < M; j++){
				resultParcial += matrixB[i][j];
			}	
			results += resultParcial;		
		}		
	}
}

void genareteRandomMatrix(){	
	int i, j;
	srand (time ( NULL));
	#pragma omp parallel shared(i, matrixA, matrixB) private(j)
	{	
		unsigned int threadId = omp_get_thread_num();
		
		#pragma omp for
		for(i = 0; i < M; i++){			
			for(j = 0; j < M; j++){
				matrixA[i][j] = rand_r(&threadId);				
			}
		}
		#pragma omp for
		for(i = 0; i < M; i++){			
			for(j = 0; j < M; j++){
				matrixB[i][j] = rand_r(&threadId);				
			}
		}
	}	
}

int main(){	
	double Ticks[2];
	Ticks[0] = omp_get_wtime();		
	omp_set_num_threads(N);
	
	genareteRandomMatrix();
	printf("Random: %lf",omp_get_wtime() - Ticks[0]);
	genareteSquare();
	genareteDiferents();
	genareteSum();
		
	Ticks[1] = omp_get_wtime();
	double Tempo = Ticks[1] - Ticks[0];
	printf("\nTempo gasto: %lf s.\n", Tempo);        
	
	return 0;
}

