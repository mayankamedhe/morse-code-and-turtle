#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <errno.h>

#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported
 
#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64
struct sigaction act;


void sig_handler(int signum)
{
    char input, input2;
    printf("\nInterrupt SIGINT received.\n");
    printf("Do you really want to quit (y|n)?\n");
    scanf("%c%c", &input, &input2);
    if(input == 'y')
    {
        exit(signum);
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

char **tokenize2(char *line)
{
    char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
    char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
    int i, tokenIndex = 0, tokenNo = 0;

    for(i =0; i < strlen(line); i++){

        char readChar = line[i];

        if (readChar == ';' || readChar == '\n') {
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

void printDir()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\nCurrent Directory: %s", cwd);
}
 
void execArgs(char** parsed)
{
    int op=0;
    int fd=0;
    for (int i = 0; parsed[i]!=NULL; i++)
    {
        if(parsed[i][0] == '>')
        {
            op = i;
            break;
        }
    }
    if(parsed[0][0] == 'e' && parsed[0][1] == 'c' && parsed[0][2] == 'h' && parsed[0][3] == 'o' && op > 0)
    {
        

        // if(op > 0)
        // {
            fd = open(parsed[op+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
             perror("r1");
             exit(1);
            }
        

        int sz1, sz2;
        pid_t cpid;
        char** buf;
        int j1=0;
        int i1=0;
    
        for (int i = 1; i < op; ++i)
        {
            sz1 = write(fd, parsed[i], strlen(parsed[i]));
            sz2 = write(fd, " ", 1);
        }
        //}
        
    }
    else
    {
        pid_t pid = fork(); 
     
         
        if (pid == 0) 
        {
            if (execvp(parsed[0], parsed) < 0) 
            {
                if (parsed[0][0] == 'c' && parsed[0][1] == 'a' && parsed[0][2] == 't')
                {
                    fprintf(stderr, "cat: %s: No such file or directory\n", parsed[1]);   
                }
            }
            exit(0);
        } 
        else 
        {
            
            wait(NULL); 
            
            return;
        }
    }

    if(fd > 0)
    {
        close(fd);
    }
}

int main()
{  
    while (1) {
        signal(SIGINT, sig_handler);
        char  line[MAX_INPUT_SIZE];            
        char  **tokens, **tokens_h;              
        int i;           
           
        printf("\nturtle>");     
        bzero(line, MAX_INPUT_SIZE);
        gets(line); 
        // line[strlen(line)] = ' ';
        // line[strlen(line)] = ';';
        // line[strlen(line)] = ';';
        //line[strlen(line)] = '\n';
        tokens_h = tokenize(line);
   
        int num_token = 0;
        int flag=0;
        for(i=0;tokens_h[i]!=NULL;i++){
            num_token++;
            if(tokens_h[i][0] == ';' && tokens_h[i][1] == ';')
            {
                flag =1;
            }
        }
        num_token++;
        if(flag == 1)
        {
            line[strlen(line)] = ' ';
            line[strlen(line)] = ';';
            line[strlen(line)] = ';';
            line[strlen(line)] = '\n';
            char  **tokens2;
            tokens2 = tokenize2(line);
            int num_token2=0;
            for(i=0;tokens2[i]!=NULL;i++)
            {
                num_token2++;
            }
            
            for(int i =0; i< num_token2; i++)
            {    

                tokens = tokenize(tokens2[i]);
                for(int j=0; tokens[j]!=NULL; j++)
                if(tokens[0][0]== 'c' && tokens[0][1] == 'd' && num_token == 2)
                {   int dir_change;
                    dir_change = chdir(tokens[1]);
                    if(dir_change == -1)
                    {
                        fprintf(stderr, "Some error\n");
                    }
                }
                else if(tokens[0][0]== 'c' && tokens[0][1] == 'd' && num_token != 2)
                {
                    fprintf(stderr, "Wrong number of arguments\n");
                }
                else
                {
                    execArgs(tokens);
                }
            }
    
            for(i=0;tokens[i]!=NULL;i++){
                free(tokens[i]);
            }
           free(tokens);
        }

        else
        {
            line[strlen(line)] = '\n';
            tokens_h = tokenize(line);
       
            if(tokens_h[0][0]== 'c' && tokens_h[0][1] == 'd' && num_token == 2)
            {   
                int dir_change;
                dir_change = chdir(tokens[1]);
                if(dir_change == -1)
                {
                    fprintf(stderr, "Some error\n");
                }
            }
            else if(tokens_h[0][0]== 'c' && tokens_h[0][1] == 'd' && num_token != 2)
            {
                fprintf(stderr, "Wrong number of arguments\n");
            }
            else
            {
                execArgs(tokens_h);
            }
            // for(i=0;tokens_h[i]!=NULL;i++)
            // {
            //     free(tokens_h[i]);
            // }

            // free(tokens_h);
            
        } 
        for(i=0;tokens_h[i]!=NULL;i++)
        {
            free(tokens_h[i]);
        }
        free(tokens_h);

    }
    return 0;
}