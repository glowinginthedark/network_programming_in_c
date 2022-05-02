#include  <stdio.h>
#include  <unistd.h>
#include  <sys/types.h>

#define   MAX_COUNT  5

// https://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/create.html

void ChildProcess(void);
void ParentProcess(void);

int main(void)
{
    pid_t  pid;

    pid = fork();
    if (pid == 0) 
          ChildProcess();
    else 
          ParentProcess();

    return 0;
}

void ChildProcess(void)
{
    int   i;

    for (i = 1; i <= MAX_COUNT; i++) {
        printf("   This line is from child, value = %d\n", i);
        sleep(1);
    }
    printf("   *** Child process is done ***\n");
}

void ParentProcess(void)
{
    int   i;

    for (i = 1; i <= MAX_COUNT; i++) {
        printf("This line is from parent, value = %d\n", i);
        sleep(1);
    }
    printf("*** Parent is done ***\n");
}