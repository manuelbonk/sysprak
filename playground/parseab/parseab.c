#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

// @param *argv[]: filename
int main (int argc, char *argv[]){
	// is there at least one filename provided?
	if (argc<2){
		printf("usage: %s [FILENAME TO PARSE]\n",argv[0]);
		return 0;
	}

	// iterate over all provided filenames
	for (int i=1; i<argc;i++){

		// save the filename i a separate variable
		char *fname = malloc(1000*sizeof(char));
		strcpy (fname,argv[i]);
		printf("argument %d: <%s>\n",i,argv[i]);

		if (access (fname, F_OK|R_OK)==-1){
			// file doesn't exist or isn't readable
			printf("<%s>: file doesn't exist or isn't readable.\n",fname);
		} else {
			// file exists and is readable

			printf("<%s>: file exists and is readable.\n",fname);
			// file handle
			FILE * fp;
			// the actual string
			char *line = NULL;
			// dunno
			size_t len = 0;
			// length of the read line
			ssize_t read;

			fp=fopen(fname, "r");

			// short excursion to using '0' as a delimiter
//			while ((read = getdelim(&line,&len,48,fp)) != -1){

			// read file line by line
			while ((read = getline(&line,&len,fp)) != -1){
//				printf("<%s>: <%s> and is <%zd> characters long.\n",fname,line,read);

				/*
				// approach with strol
				long int val = strtol(line,NULL,10);
				printf("<%s>: <%ld> has been extracted of <%s>\n",fname,val,line);
				*/

				// go through every character
				char key;
				int val;
//				long int val;
				for (int j=0;j<read;j++){
//					printf("<%5s>: pos: <%02d>: <%3c> and it is ",fname,j,line[j]);
					if (isspace(line[j])){
//							printf("    whitespace.\n");
						}
					else if (isalpha(line[j])){
//							printf("   a character.\n");
							key=line[j];
						}
					else if (isdigit(line[j])){
//							printf("       a digit.\n");
						}
					else if (line[j]=='='){
							//printf("a '='.\n\nline: <%s\nwe're at <%c>.\nrest of the string: <%s>\n",line,line[j],line+j+1);
//							printf("line: <%s\nwe're at <%c>.\nrest of the string: <%s>\n",line,line[j],line+j+1);
							// val=strtol(line+j+1,NULL,10);
							val = atoi(line+j+1);
							printf("key: <%c> value: <%d>\n",key,val);
							break;
						}
					else{
							printf("something else.\n");
						}
				}
			}
			fclose(fp);
		}
	}
	return 0;
}
