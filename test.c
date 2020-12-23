#include <stdio.h>

	
void(*message(int hour))()


void fn(char *str)
{
    printf("Im here = %s", str);
}

void fn1(void (**function)(char *str))
{
    *function = fn;
}

int main ()
{
    void	(*function)(char *str);
    char *str = "Im str";

    fn1(&function);
    function(str);
    return(0);
}