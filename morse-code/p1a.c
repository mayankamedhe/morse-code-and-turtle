#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

struct sigaction act;

void sig_handler(int signum)
{
	char input, input2;
	printf("\nInterrupt SIGINT received.\n");
    printf("Do you really want to quit (y|n)?\n");
    scanf("%c%c", &input, &input2);
    //printf("val of input- %c",input);
    if(input == 'y')
    {
    	//printf("a1\n");
    	exit(signum);
    }
    // else if(input == '\n')
    // {
    // 	printf("a3\n");
    // }
    // printf("a2\n");
    //input = NULL;
}

void sighandler2(int signum, siginfo_t *info, void *ptr)
{
	char input, input2;
    printf("\nInterrupt SIGTERM received.\n");
    printf("\nDo you really want to quit (y|n)?\n");
    scanf("%c%c", &input, &input2);
    //printf("a2\n");
    if(input == 'y')
    {
    //	printf("a1\n");
    	exit(signum);
    }
    //printf("a3\n");
}

int main()
{
	//printf("I am %lu\n", (unsigned long)getpid());
	memset(&act, 0, sizeof(act));
	act.sa_sigaction = sighandler2;
    act.sa_flags = SA_SIGINFO;
    while(1)
    {
    signal(SIGINT, sig_handler);
    sigaction(SIGTERM, &act, NULL);
    
    	sleep(30); // This is your chance to press CTRL-C
     }
    return 0;
}

