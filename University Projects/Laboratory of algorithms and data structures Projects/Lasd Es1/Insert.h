#include <conio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

char* InputStr();
int* InputInt();
float InputFloat();

char* InputStr(){
    int i=0;
    char * stringa=NULL,temp;
    stringa=(char*)malloc(sizeof(char));
    fflush(stdin);
    while((temp=getchar())!='\n'){
           stringa[i]=temp;
           i++;
           stringa=(char*)realloc(stringa,(i+1)*sizeof(char));
    }
    stringa[i]='\0';
    fflush(stdin);
    return stringa;
}

int* InputInt(){
    char valore[100];
 	int i=0;
 	int* res;
	gets(valore);
	for(i=0;valore[i]<0 || valore[i]>32;i++);
	valore[i]=0;
	fflush(stdin);
	res=malloc(sizeof(int));
	*res=atoi(valore);
    return res;
}

float InputFloat(){
    char valore[100];
 	int i=0;
	gets(valore);
	for(i=0;valore[i]<0 || valore[i]>32;i++);
	valore[i]=0;
	fflush(stdin);
	return atof(valore);

}

int* RandInt(){
    int* i;
    i=malloc(sizeof(int));
    *i=rand()%400;
    return i;
}

float* RandFlt(){
    float* i;
    i=(float*)malloc(sizeof(float));
    *i=(float)rand() + (float)(rand()/(float)RAND_MAX);
    return i;
}

char* RandStr(){
    char* i;
    int j=0;
    i=malloc(sizeof(char)*5);
    for(j=0;j<5;j++){
        i[j]=(char)((rand()%25)+97);
    }
    return i;
}

