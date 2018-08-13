#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

void sig_handler(int signum)
{
    if (signum == 2)
    {printf("Please use the exit command to quit the shell\n"); }
    else {exit(0);}
}

void executor(char * line, char * tokens[])
{
    bool juggle = false;
    int juggler = -1;
    for (int i = 0 ; tokens[i] != NULL ; i ++)
    {
        if (tokens[i][0] == '>') {juggle = true; juggler = i;}
        //printf("%s %d\n", tokens[i], juggle);
    }
    //printf("\n");
    if (juggle)
    {
      //  printf("came here\n");
        if (tokens[juggler + 1] == NULL || tokens[juggler + 2] != NULL)
        {
            fprintf(stderr, "There was no file or too many files to the right of '>'\n" );
        }
        int pid = fork();
        if (pid == 0)
        {
            int fd = open(tokens[juggler + 1], O_RDWR | O_CREAT, S_IRWXU);
            dup2(fd, 1);
            char * current[MAX_TOKEN_SIZE];
            for (int i = 0 ; i < juggler ; i ++)
            {
                current[i] = tokens[i];
            }
            tokens[juggler] = NULL;
        



            if (strcmp(line, "exit\n") == 0)//exit
            {
                exit(0);
            }

            if (strcmp(tokens[0], "cd") == 0) // for cd
            {
                int n = 0;
                while (tokens[n] != NULL) n ++;
                if (n != 2)
                {
                    fprintf(stderr, "An incorrect number of arguments was passed to cd\n");
                    return ;
                }
                int returnStat = chdir(tokens[1]);
                if (returnStat != 0)
                {
                    fprintf(stderr, "There was an error executing the cd command\nEnsure that the argument is indeed a directory\n");
                }
            }

            else //default for standalone function calls
            {
                int n = 0;
                while (tokens[n] != NULL) n ++;
                //for (int i = 0 ; i < n ; i ++ ) printf("%s ", tokens[i]); printf ("\n");
                if (n == 0) return ;
                execvp(tokens[0], tokens);
                fprintf(stderr, "There was an error in executing this command\n");
                
            }
            exit(0);




            printf("coming here\n");
        }
        else
        {
            wait(NULL);
        }
    }
    else
    {
        if (strcmp(line, "exit\n") == 0)//exit
        {
            exit(0);
        }

        if (strcmp(tokens[0], "cd") == 0) // for cd
        {
            int n = 0;
            while (tokens[n] != NULL) n ++;
            if (n != 2)
            {
                fprintf(stderr, "An incorrect number of arguments was passed to cd\n");
                return ;
            }
            int returnStat = chdir(tokens[1]);
            if (returnStat != 0)
            {
                fprintf(stderr, "There was an error executing the cd command\nEnsure that the argument is indeed a directory\n");
            }
        }

        else //default for standalone function calls
        {
            int n = 0;
            while (tokens[n] != NULL) n ++;
            //for (int i = 0 ; i < n ; i ++ ) printf("%s ", tokens[i]); printf ("\n");
            if (n == 0) return ;
            int pid = fork();
            if (pid == 0)
            {
                execvp(tokens[0], tokens);
                printf("There was an error in executing this command\n");
                exit(0);
            }
            else
            {
                wait(NULL);
            }
        }
    }

}

char **tokenize(char *line)
{
    char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
    char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
    int i, tokenIndex = 0, tokenNo = 0;

    for(i =0; i < strlen(line); i++){

        char readChar = line[i];

        if (readChar == ' ' || readChar == '\n' || readChar == '\t') {
            token[tokenIndex] = '\0';
            if (tokenIndex != 0){
                tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
                strcpy(tokens[tokenNo++], token);
                tokenIndex = 0; 
            }
        } 
        else {
            token[tokenIndex++] = readChar;
        }
    }
 
    free(token);
    tokens[tokenNo] = NULL ;
    return tokens;
}

void main(void)
{
    signal(SIGINT, sig_handler);
    char  line[MAX_INPUT_SIZE];            
    char  **tokens;              
    int i;

    while (1) {           
       
        printf("Hello>");     
        bzero(line, MAX_INPUT_SIZE);
        gets(line);           
        line[strlen(line)] = '\n'; //terminate with new line
        tokens = tokenize(line);
   
        // printf("Got command %s", line);
        // for(i=0;tokens[i]!=NULL;i++){
        //     printf("found token %s\n", tokens[i]);
        // }

        if (line[0] == '\n') continue;

        bool multiple = false;
        for (int i = 0 ; tokens[i] != NULL ; i ++)
        {
            if (tokens[i][0] == ';' && tokens[i][1] == ';') {multiple = true;}
        }

        //to accomodate multiple commands separated by ";;"
        if (multiple)
        {
            char * current[MAX_INPUT_SIZE];
            int index = 0;
            int i = 0;
            while (tokens[index] != NULL)
            {
                if (tokens[index][0] == ';' && tokens[index][1] == ';')
                {
                    current[i] = NULL;
                    executor(line, current);
                    for (i = 0 ; current[i] != NULL ; i ++)
                    {
                        free(current[i]);
                    }
                    i = 0;
                }
                else
                {
                    current[i] = tokens[index];
                    i++;
                }
                index ++;
            }
            current[i] = NULL;
            executor(line, current);
            for (i = 0 ; current[i] != NULL ; i ++)
            {
                free(current[i]);
            }
        }
        else
        {
            executor(line, tokens);
        }
        
       
        // Freeing the allocated memory	
        for(i=0;tokens[i]!=NULL;i++){
            free(tokens[i]);
        }
        free(tokens);
    }
     

}

                
