#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

void optionOne(){
    char *s = (char *) malloc(100);
    strncpy(s, "Welcome Sanitizer!", 99);
    s[99] = '\0';
    printf("string is: %s\n", s);
    free(s);
}

void optionTwo(){
    char *s = (char *) malloc(100);
    strncpy(s, "Welcome Sanitizer!", 99);
    s[99] = '\0';
    printf("string is: %s\n", s);
    free(s);
}

void optionThree(){
    char *s = (char *) malloc(100);
    //free(s);
    
     s=NULL;
    
    s = (char *) malloc(100); //asignamos memoria nuevamente 
    strncpy(s, "Welcome Sanitizer!", 99);
    s[99] = '\0';
    printf("string is: %s\n", s);
    free(s);
}

void optionFour(){
    char *s = (char *) malloc(20);
    strncpy(s, "Welcome Sanitizer!", 19);
    s[19] = '\0';
    printf("string is: %s\n", s);
    free(s);
}

int main(int argc, const char *argv[]) {

    int expression;
    char* p;
    errno = 0; 
    
    if (2 != argc) {
        fprintf(stderr, "Usage: %s <option>\n", argv[0]);
        exit(1);
    }

    long arg = strtol(argv[1], &p, 10);

    if (*p != '\0' || errno != 0) {
        return 1; 
    }

    if (arg < INT_MIN || arg > INT_MAX) {
        return 1;
    }

    expression = arg;
 

    switch (expression)
    {
        case 1:
            optionOne();
            break;
        case 2:
            optionTwo();
            break;
        case 3:
            optionThree();
            break;
        case 4:
            optionFour();
            break;
        default:
            printf("\n");
            break;
    }

    return 0;
}
