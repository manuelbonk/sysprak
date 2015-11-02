#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** generateMatrix(int n){
	// pointer to n*n ints
	int* values = calloc(n*n,sizeof(int));
	int** rows = malloc(n*sizeof(int*));
	for (int i=0;i<n;++i){
		// mark every nth as the beginning of a new row
		rows[i] = values+i*n;
	}

	// insert random values
	for (int a=0;a<n;a++){
		for (int b=0;b<n;b++){
		rows[a][b]=rand()%5;
		}
	}

	return rows;
}

void printMatrix(int** matrix,int n){
	for (int row=0;row<n;row++){
		printf("(");
		for (int col=0;col<n;col++){
		//printf("[%2d][%2d]: <%2d>\n",a,b,matrix[a][b]);
		printf("%2d ",matrix[row][col]);
		}
		printf(")\n");
	}
//	printf("========================================\n");
}

int** multiplyMatrices(int** m0, int** m1,int n){
	int** result = generateMatrix(n);

	for (int row=0;row<n;row++){
		for (int col=0;col<n;col++){
			//calculate cell vaule
			int cell=0;
			for (int i=0;i<n;i++){
				int temp=m0[row][i]*m1[i][col];
//				printf("m0[%d][%d]*m1[%d][%d]\n <%d> * <%d> = <%2d>\n",row,i,i,col,m0[row][i],m1[i][col],temp);
				cell+=temp;

			}
//			printf("res[%d][%d]=<%d>\n\n",row,col,cell);
			result[row][col]=cell;
		}
	}
	return result;
}

int main(int argc, char *argv[]){
	if (argc != 2){
		fprintf(stderr, "usage %s: <matrix size>\n", argv[0]);
		return 1;
		}
	int n = strtol(argv[1],NULL,10);

//	printf("n = <%i>\n",n);
	srand(time(NULL));
	int** m0 = generateMatrix(n);
//	printMatrix(m0,n);
	int** m1 = generateMatrix(n);
//	printMatrix(m1,n);
	int** result = multiplyMatrices(m0,m1,n);
	printf("matrix 0:\n");
	printMatrix(m0,n);
	printf("\nmatrix 1:\n");
	printMatrix(m1,n);
	printf("\nmatrix 0 * matrix 1:\n");
	printMatrix(result,n);

	return 0;
}
