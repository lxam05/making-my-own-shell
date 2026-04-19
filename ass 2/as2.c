#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    while(1){

        char *line = NULL;
        size_t len = 0;
        ssize_t read;

        read = getline(&line, &len, stdin);
        if(read == -1){
            printf("Error reading file");
            return 0;
        }

        line[strcspn(line, "\n")] = '\0';
        char **output_str = NULL;
        int count = 0;
        char* temp = strtok(line, " ");
        while(temp != NULL){
            output_str = realloc(output_str, (count + 2) * sizeof(char*));
            output_str[count] = temp;
            count++;        
            temp = strtok(NULL, " ");
        }
        output_str[count] = NULL;

        int pid = fork();

        if(pid == 0){
            execvp(output_str[0], output_str);
            printf("Failed execvp");
            exit(1);
        }else{
            wait(NULL);
        }
    }
}