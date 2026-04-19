#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){

    execvp("bin/ls", argc, environ);
    printf("Hello?");
}