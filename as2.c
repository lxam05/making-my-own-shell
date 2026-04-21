#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>

static void catch_function(int signo){
    write(1, "\n# ", 3);
}

int main(int argc, char *argv[]){

    while(1){



        char *line = NULL;
        size_t len = 0;
        ssize_t read;

        time_t currentTime;
        time(&currentTime);

        char *t = ctime(&currentTime);
        if (t[strlen(t)-1] == '\n') t[strlen(t)-1] = '\0';
        printf("%s # ", t);

        if(signal(SIGINT, catch_function)){
            write(1, "\n> ", 3);
        }

        read = getline(&line, &len, stdin);
        if(read == -1){
            printf("Error reading file\n");
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


        if(output_str[0] != NULL){
            if(strcmp(output_str[0], "cd") == 0){

                char *path = getenv("HOME");

                if(output_str[1] != NULL){
                    chdir(output_str[1]);
                }else if(path != NULL){
                    chdir(path);
                }else{
                    perror("cd");
                }

            }else{

                int pid = fork();

                if(pid == 0){
                    execvp(output_str[0], output_str);
                    printf("\nFailed execvp");
                    exit(1);
                }else{
                    wait(NULL);
                }
            }
        }
    }
}
