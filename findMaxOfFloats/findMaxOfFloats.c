#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char *argv[]){
	char filename[256];

	if (argc<2){
		printf("Which file should be read?\t(press ^d to quit input)\n");
		fgets(filename,sizeof(filename),stdin);
//	printf("\nYou've inserted: <%s>\n",filename);

	}
	else {
		strcpy(filename,argv[1]);
		}
	printf("filename = <%s>\n",filename);

	// check if file exists
	if( access(filename, F_OK) == -1 ) {
		perror("Error opening file");
		return EXIT_FAILURE;
	}

	float values[10000];
//	float *values;
	int i =0;

	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	fp=fopen(filename,"r");
	while ((read = getline(&line,&len,fp))!= -1){
		printf("retrieved line of length: <%zu>\n",read);
//		printf("%s\n",line);
//		*(values++)=strtod(line,NULL);
		values[i++]=strtod(line,NULL);
	}

	float max;
	while(i>0){
		printf("val: <%f>\n", values[--i]);
		if (values[i]>max) max=values[i];
		i--;
//		if (*(--values)>max) max=values[i];
	}
	printf("max. value: <%f>\n",max);

	fclose(fp);
	return 0;
}
