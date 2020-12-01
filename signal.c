# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int flag;

void	fn(int sig)
{
    flag = 1;
    write(1, "\nSignal caught_nf\n", 15);
}

int main()
{
    void (*ptr)(int);
    char c;

    flag = 0;
    signal(SIGINT, &fn);
	signal(SIGQUIT, &fn);
//	signal(SIGTSTP, &fn);
    while(1)
    {
        if (read(0, &c, 1) > 0 || flag == 1)
            write(1, &c, 1);
        if (flag == 1)
        {
            write(1, "\nSignal caught\n", 15);
            flag = 0;
        }
    }
    return(0);
}