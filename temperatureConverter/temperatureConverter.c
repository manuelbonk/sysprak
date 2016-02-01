#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert(char *value, char *from, char *to){
	double val= strtod(value,NULL);
	double result=0;
	printf("trying to convert %f %s to %s\n", val,from, to);
	if     (strcmp(from,"C")==0 && strcmp(to,"De")==0)  result=(100-val)*1.5;
	else if(strcmp(from,"C")==0 && strcmp(to,"F")==0)   result=val*1.8+32;
	else if(strcmp(from,"C")==0 && strcmp(to,"K")==0)   result=val+273.15;
	else if(strcmp(from,"C")==0 && strcmp(to,"Ra")==0)  result=val*1.8+491.67;

	else if(strcmp(from,"De")==0 && strcmp(to,"C")==0)  result=100-val*2/3;
	else if(strcmp(from,"De")==0 && strcmp(to,"F")==0)  result=212-val*1.2;
	else if(strcmp(from,"De")==0 && strcmp(to,"K")==0)  result=373.15-val*2/3;
	else if(strcmp(from,"De")==0 && strcmp(to,"Ra")==0) result=671.67-val*1.2;

	else if(strcmp(from,"F")==0 && strcmp(to,"C")==0)   result=(val-32)*5/9;
	else if(strcmp(from,"F")==0 && strcmp(to,"De")==0)  result=(212-val)*5/6;
	else if(strcmp(from,"F")==0 && strcmp(to,"K")==0)   result=(val+459.67)*5/9;
	else if(strcmp(from,"F")==0 && strcmp(to,"Ra")==0)  result=val+459.67;

	else if(strcmp(from,"K")==0 && strcmp(to,"C")==0)   result=val-273.15;
	else if(strcmp(from,"K")==0 && strcmp(to,"De")==0)  result=(373.15-val)*1.5;
	else if(strcmp(from,"K")==0 && strcmp(to,"F")==0)   result=val*1.8-459.67;
	else if(strcmp(from,"K")==0 && strcmp(to,"Ra")==0)  result=val*1.8;

	else if(strcmp(from,"Ra")==0 && strcmp(to,"C")==0)  result=val*5/9-273.15;
	else if(strcmp(from,"Ra")==0 && strcmp(to,"De")==0) result=(671-val)*5/6;
	else if(strcmp(from,"Ra")==0 && strcmp(to,"F")==0)  result=val-459.67;
	else if(strcmp(from,"Ra")==0 && strcmp(to,"K")==0)  result=val-5/9;

	else if(strcmp(from,to)==0) result=val;
	else {
		printf("<%s> or <%s> are no proper units!",from,to);
		return;
		}
	printf("%f %s are %f %s!\n",val,from,result,to);
}

int validateValue(char input[]){
	int isFloat=0;
	while (*input != '\0') {
//		printf("input is: %c\n", *input);
		if(*input >= '0' && *input < '9') {
		}
		else if(*input == '.') {
				if (isFloat == 0){
					isFloat=1;
				}
				else {
					printf("input is not valid\n");
//					printf("%s is not a valid input\n",&input);
					return 1;
				}
			}
		else {
					printf("input is not valid\n");
//					printf("%s is not a valid input\n",&input);
					return 1;
		}
		input++;
	}
//	printf("input is valid and is a float (y=1,n=0): %d\n", isFloat);
	return 0;
}

int main(int argc, char *argv[]){
	if (argc < 4) {
		fprintf(stderr,"usage: %s: <value> <unit> <target unit>\n", argv[0]);
		return 1;
		}
	for (int i=0;i<argc;i++){
		printf("parameter no. %d:\t%s\n", i,argv[i]);
	}

//	if (argv[1][0]>0 && argv[1][0]<=9) printf("\n%c > 0\n\n", argv[1][0]);
	if (validateValue(argv[1])!=0) return 1;

	convert(argv[1], argv[2],argv[3]);

	return 0;
	}
