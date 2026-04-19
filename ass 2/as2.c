#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){

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

    for(int i = 0; i < count; i++){
        printf("%s\n", output_str[i]);
    }
}