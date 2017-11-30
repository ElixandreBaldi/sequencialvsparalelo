#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define M 14750

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
	printf("results: %lf",results);	
}

void genareteSquare(){
	for(int i = 0; i < M; i++){
		for(int j = 0; j < M; j++){
			matrixA[i][j] = matrixA[i][j]*matrixA[i][j];
			matrixB[i][j] = matrixB[i][j]*matrixB[i][j];
		}	
	}	
}

void genareteDiferents(){
	for(int i = 0; i < M; i++){
		for(int j = 0; j < M; j++){
			matrixB[i][j] = matrixA[i][j] - matrixB[i][j];
		}	
	}		
}

void genareteSum(){
	for(int i = 0; i < M; i++){
		for(int j = 0; j < M; j++){
			results += matrixB[i][j];
		}	
	}		
}

void generateRandomMatrix(){
	srand ( time ( NULL));
	for(int i = 0; i < M; i++){
		for(int j = 0; j < M; j++){
			matrixA[i][j] = rand();
			matrixB[i][j] = rand();
		}
	}
}

int main(){	
	
	clock_t Ticks[2];
    Ticks[0] = clock();
    
	
	generateRandomMatrix();	
	printf("Random: %lf", (double)(clock() - Ticks[0]));
	genareteSquare();
	genareteDiferents();
	genareteSum();	
	Ticks[1] = clock();
	
    double Tempo = ((double)(Ticks[1] - Ticks[0])/ CLOCKS_PER_SEC);
    printf("\nTempo gasto: %lf s.\n", Tempo);    
	return 0;
}
