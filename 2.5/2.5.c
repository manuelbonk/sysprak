#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void updateLeaderboard(int* highscores, char* leaderboard, int length){
		FILE * fp_lb= fopen(leaderboard,"w");
		printf("len: <%d>\n",length);
		for (int i=0;i<length;i++) fprintf  (fp_lb,"%03d\n",*(highscores++));
		fclose(fp_lb);
}

int startGame(int counter, int zufallszahl){
	printf("zufallszahl: <%03d>\n",zufallszahl);
	char input[256];
	printf("Please guess a number between 1 and 100.\n");
	fgets(input,sizeof(input),stdin);
	int guess = strtod(input,NULL);

	if (counter>99) {
		printf("r u srs?\n");
		return counter;
	}

	// validate input
	if (guess < 1 || guess >100) {
		printf("%d is not a number between 1 and 100.\n",guess);
		return startGame(counter,zufallszahl);
	}
	if (guess < zufallszahl){
		printf("The random number is greater than %3d.\n",guess);
		return startGame(++counter,zufallszahl);
		}
	if (guess > zufallszahl){
		printf("The random number is less than %3d.\n",guess);
		return startGame(++counter,zufallszahl);
		}
	printf("Yay, %d is correct, you've had %d attempts!\n",guess,counter);

	// write logfile
	FILE * fp_log = fopen("zahlenraten.log","a");
	fprintf  (fp_log,"%3d,%d\n",zufallszahl,counter);
	fclose(fp_log);

	// leaderboard
	char *leaderboard = "leaderboard";
	if (access(leaderboard, F_OK)!=-1){
		printf("leaderboard exists.\n");
		FILE * fp_lb = fopen(leaderboard,"r+");

		int maxlen = 10;
		char line[maxlen];
		int linecount = 0;
		// semaphore to check if value was already inserted
		int inserted = 0;
		int newfile[maxlen];
		printf("counter: <%03d>\n",counter);
		while (!feof(fp_lb) && linecount<maxlen){
			fgets(line,10,fp_lb);
			int lineval = strtod(line,NULL);
			if (counter <= lineval && inserted == 0){
				newfile[linecount++]=counter;
				inserted++;
				printf("CURRENT COUNTER <%02d>\n",counter);
				printf("hier muss eine Zeile eingefügt werden.\n-> <%s>, line %02d: %d\n",leaderboard,linecount,counter);
			}
			newfile[linecount++]=lineval;
			printf("<%s>, line %02d: %03d\n",leaderboard,linecount,lineval);
		}
		fclose(fp_lb);
		updateLeaderboard(newfile,leaderboard,linecount);

//		for (int i = 0;i<linecount;


	}
	else {
		printf("leaderboard does not exist.\n");
		FILE * fp_lb= fopen(leaderboard,"a");
		fprintf  (fp_lb,"%02d\n",counter);
		fclose(fp_lb);
	}

	// new game
	printf("Wanna play again? (yes = 1, no = 0)\n");
	char replay[256];
	fgets(replay,sizeof(replay),stdin);
	int yn = strtod(replay,NULL);
	if (yn==1) return startGame(0,rand()%9+1);
	return counter;
}


int main (int argc, char *argv[]){
	srand(time(NULL));
	int zufallszahl = rand()%9 +1;
	int counter = 1;
	startGame(counter, zufallszahl);
	return 0;
}
