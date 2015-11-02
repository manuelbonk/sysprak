#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void printBoard(int** board,int size){
	for (int y=0;y<size;y++){
		for (int x=0;x<size;x++){
			printf("%2d",board[x][y]);
//			printf("%d|%d:%2d\t",x,y,board[x][y]);
//			printf("board[%2d][%2d]: <%d>\n",x,y,board[x][y]);
		}
		printf("\n");
	}
	printf("\n");
}
int** generateBoard(float density, int size){

	int* values = calloc(size*size,sizeof(int));
	int** board = malloc(size*sizeof(int*));
	for (int i=0;i<size;++i){
		//mark every nth as the beginning of a new row
		board[i] = values+i*size;
	}

	int rest = size*size*density;

	while(rest>0){
//		printf("rest: <%d>\n",  rest);
		int x = rand()%size;
		int y = rand()%size;
		if(board[x][y]==0){
			board[x][y]=1;
			rest--;
		}
	}
//	printBoard(board,size);

	return board;
}

int getNeighbors(int** board,int size, int x, int y){
	size--;
	int result;
	if (x == 0 && y == 0) result=board[x+1][y]+board[x][y+1]+board[x+1][y+1];
	else if (x == size && y == 0) result=board[x-1][y]+board[x-1][y+1]+board[x][y+1];
	else if (x == 0 && y == size) result=board[x][y-1]+board[x][y-1]+board[x+1][y];
	else if (x == size && y == size) result=board[x-1][y-1]+board[x-1][y]+board[x][y-1];
	else if (y == 0) result=board[x-1][y]+board[x+1][y]+board[x-1][y+1]+board[x][y+1]+board[x+1][y+1];
	else if (x == size) result=board[x-1][y-1]+board[x][y-1]+board[x-1][y]+board[x-1][y+1]+board[x][y+1];
	else if (y == size) result=board[x-1][y-1]+board[x][y-1]+board[x+1][y-1]+board[x-1][y]+board[x+1][y];
	else if (x == 0) result=board[x][y-1]+board[x+1][y-1]+board[x+1][y]+board[x][y+1]+board[x+1][y+1];
	else result =board[x-1][y+1]+board[x][y+1]+board[x+1][y+1]+board[x-1][y]+board[x+1][y]+board[x-1][y-1]+board[x][y-1]+board[x+1][y-1];

//	printf("board[%2d][%2d] has %d neighbors.\n",x,y,result);
	return result;
}

int** update(int** board, int size){
	int** nextBoard = generateBoard(0,size);
	int unchanged=0;
	for(int y = 0; y < size; y++){
		for(int x = 0; x < size; x++){
			int neighbors = getNeighbors(board,size,x,y);
			if((neighbors < 2 || neighbors > 3) && board[x][y]==1)nextBoard[x][y] = 0;
			else if(neighbors == 3) nextBoard[x][y] = 1;
			else if (neighbors == 2 && board[x][y] == 0) nextBoard[x][y] = 0;
			else if (neighbors == 2 && board[x][y] == 1) nextBoard[x][y] = 1;

			if (board[x][y] == nextBoard[x][y]) unchanged++;
		}
	}
	if (unchanged == size*size) return nextBoard;
	printBoard(nextBoard,size);

/*
	struct timespec(), tim(), tim2();
	tim.tv_sec=1;
	tim.tv.nsec= 500000000L;
	if (nanosleep(&tim,&tim2)<0){
		printf("Nano  sleep system call failed.\n");
		return -1;
		}
*/
	sleep(1);

	return update(nextBoard,size);
}

int main (int argc,char *argv[]){

	srand(time(NULL));
	int size=16;
	float density;
	switch(argc){
		case 2:
			printf("yay, ein parameter\n");
			density=strtod(argv[1],NULL);
			break;

		case 3:
			density=strtod(argv[1],NULL);
			size = strtol(argv[2],NULL,10);
			break;

		default:
			printf("usage: %s [density] <size>\n",*argv);
			return -1;
	}

	if (size<1 || density > 1 || density < 0){
			printf("usage: %s [density] <size>\n",*argv);
			return -1;
	}
	printf("size: <%d>\ndensity: <%f>\n",size,density);

//	static int board[size][size];
	int** board = generateBoard(density,size);
	update(board,size);
//	getNeighbors(board,size-1,0,0);
//	getNeighbors(board,size-1,0,size);
//	getNeighbors(board,size-1,size-1,0);
//	getNeighbors(board,size-1,size-1,size-1);
//	getNeighbors(board,size,2,2);

}
