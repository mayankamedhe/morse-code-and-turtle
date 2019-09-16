#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

void my_sigchld_handler(int sig)
{
    //printf("inside func\n");
    pid_t p;
    int status;

    p=waitpid(-1, &status, WNOHANG);
    printf("Parent %d: Child %d is exited\n", getpid(), p); 
}

struct sigaction sa;

int main(int argc, char const *argv[])
{
    int n = 2;
    rec_child(n);
    return 0;


}

void rec_child(int n)
{
    pid_t cpid;
    int i;
    i=fork();

    if(n <= 0)
    {
        return;
    }
    else
    {
        if(i==0)
        {

            
            if(n == 2)
            {
                printf("Child %d is created by parent %d (sleeps for 9 seconds)\n", getpid(), getppid());
                sleep(9);
            }
            else if(n == 1)
            {
                printf("Child %d is created by parent %d (sleeps for 4 seconds)\n", getpid(), getppid());
                sleep(4);
            }
            rec_child(n-1);
        }
        else
        {
            // cpid = wait(NULL);
            // printf("Child %d exited\n", i);

            signal(SIGCHLD, my_sigchld_handler);
            while(1){}
        }
    }
}