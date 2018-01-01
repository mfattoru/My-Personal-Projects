#include <string.h>

int CompareInt(int* x,int* y);
int CompareFloat(float* x,float* y);
int CompareString(char* x,char* y);

int CompareInt(int* x,int* y){
    int res=0;
    if(*x > *y){
        res=1;
    }
    else if(*x < *y){
        res=-1;
    }
    else{
        res=0;
    }
    return res;
}

int CompareFloat(float* x,float* y){
    int res;
    if(*x > *y){
        res=1;
    }
    else if (*x < *y){
        res=-1;
    }
    else{
        res=0;
    }
    return res;
}

int CompareString(char* x,char* y){
    int res;
    if(strcmp(x,y)>0){
        res=1;
    }
    else if(strcmp(x,y)<0){
        res=-1;
    }
    else{
        res=0;
    }
    return res;
}

