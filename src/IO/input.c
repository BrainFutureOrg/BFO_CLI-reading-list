#include "input.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

int equal(char *a, char *b){
    while (*(a++)!='\0')
    {
        if (*(b++)=='\0')
            return 0;
        if (*a!=*b)
            return 0;
    }
    if (*b!='\0')
        return 0;
    return 1;
}


int is_int(char *str){
    char *p = str;
    if (!(*p == '-' ||*p == '+'||(*p>='0' && *p <='9'))){
        errno = ENOEXEC;
        return 0;
    }
    while(*(++p)!='\0'){
        if (!(*p>='0' && *p <='9')){
        errno = ENOEXEC;
        return 0;
    }
    }
    return 1;
}

int is_double(char *str){
    char *p = str;
    if (!(*p == '-' ||*p == '+'||(*p>='0' && *p <='9'))){
        errno = ENOEXEC;
        return 0;
    }
    int isdot=0;
    while(*(++p)!='\0'){
        if (!(*p>='0' && *p <='9')){
            if(*p=='.') {
                if(isdot){
                    errno = ENOEXEC;
                    return 0;
                }
                isdot = 1;
            }
            else{
                errno = ENOEXEC;
                return 0;
            }
    }
    }
    return 1;
}

int return_int_str(char *str){

    int sign=1;
    char *p=str;
    if (*p == '+' || *p == '-'){
        p++;
        if (*p == '-')
            sign=-1;
    }
    int a=*(p++)-'0';
    while (*p!='\0' && *p!='.')
        a = a*10 + *(p++)-'0';

    return a*sign;
}

double return_double_part(char *str){
    char *p=str;
    int isdot=0;
    while(*(p++)!='\0')
        if(*p=='.'){
            isdot=1;
            break;
        }
    if (!isdot)
        return 0;
    p++;
    int num = 1;
    double a = (*p-'0')/pow(10,num);
    while (*(++p)!='\0')
    {
        num++;
        a += (*p-'0')/pow(10,num);
    }
    return a;


}

int input_int(const char *msg){
    puts(msg);
    char* integer = input_string();
    if (is_int(integer))
        return return_int_str(integer);
    return 0;
}

long int input_long(const char *msg){
    puts(msg);
    char* integer = input_string();
    if (is_int(integer))
        return return_int_str(integer);
    return 0;
}

double input_double(const char *msg){
    puts(msg);
    char* double_number = input_string();
    if (is_double(double_number)){
        double a = return_int_str(double_number);
        a += return_double_part(double_number);
        return a;
    }
    return 0;
}

char * input_string(){
    int i=0, j = 5;
    char *str = (char*)calloc(j,sizeof(char));
    while((*(str+i)=getchar())!='\n'){
        i++;
        if (i >= j){
            j *= 2;
            str = (char*)realloc(str,j);
        }
    }
    *(str+i)='\0';
    return str;
}