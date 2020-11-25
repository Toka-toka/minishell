# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void	fn(int sig)
{
	printf("i cautch a signal = %d", sig);
    write(1, "\n", 1);
//    exit(100);
}

int main()
{
    char buf[1];
    
//    signal(SIGINT, fn);
//    signal(SIGTERM, fn);
//    signal(SIGSEGV, fn);
//    signal(SIGQUIT, fn);
    while(read(1, buf, 1) > 0)
        write(1, buf, 1);
    return(0);
}