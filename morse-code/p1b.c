// #include <stdio.h>
// #include <sys/wait.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <time.h>

// void my_sigchld_handler(int sig)
// {
//     pid_t p;
//     int status;

//     while ((p=waitpid(-1, &status, WNOHANG)) != -1)
//     {
//         printf("Child %d is exited\n", p); 
//     }
//     printf("outside\n");
// }

// struct sigaction sa;

// int main(int argc, char const *argv[])
// {
//     memset(&sa, 0, sizeof(sa));
//     sa.sa_handler = my_sigchld_handler;
    

//     int n = atoi(argv[1]);
//     int fork_int;
//     pid_t cpid;

//     srand(time(0));
    
//     // printf("Parent is : %d\n", getpid());
//     // printf("Number of children: %d\n",n);
    
//     for(int i=0;i<n;i++)
//     {
//         int delay;
//         delay = rand()%1000000;
//         //printf("%d\n", delay);
        
//         fork_int = fork();
//         if(fork_int == 0)
//         {
//             usleep(delay%10);
//             printf("Child %d is created (sleeps for %d seconds)\n",getpid(), delay%10);
//             exit(0);
//         }
//     }

//     if(fork_int != 0)
//     {
//         for (int i = 0; i < n; ++i)
//         {
//            sigaction(SIGCHLD, &sa, NULL); 
//            printf("in for loop\n");
//         }
    
//     }
    
// }



#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void my_sigchld_handler(int sig)
{
    //printf("inside func\n");
    pid_t p;
    int status;

    p=waitpid(-1, &status, WNOHANG);
    printf("Child %d is exited\n", p); 
}

struct sigaction sa;

int main(int argc, char const *argv[])
{
    int n = atoi(argv[1]);
    int fork_int;
    pid_t cpid;

    srand(time(0));
    
    // printf("Parent is : %d\n", getpid());
    // printf("Number of children: %d\n",n);
    
    for(int i=0;i<n;i++)
    {
        int delay;
        delay = rand()%10000000;
        //printf("%d\n", delay);
        
        fork_int = fork();
        if(fork_int == 0)
        {
            printf("Child %d is created (sleeps for %d seconds)\n",getpid(), delay/1000000);
            usleep(delay/10);
            exit(0);
        }
    }

    if(fork_int != 0)
    {
        // for (int i = 0; i < n; ++i)
        // {
            signal(SIGCHLD, my_sigchld_handler);
            //sigaction(SIGCHLD, &sa, NULL);
            
        // }
           
            while(1)
            {

            }
    }
    
}