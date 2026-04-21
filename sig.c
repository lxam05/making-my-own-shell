#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void catch_function(int signo){
    printf("Interactive attention signal caught.\n");
}

int main(){

    while(1){

        signal(SIGINT, catch_function);

    }

}