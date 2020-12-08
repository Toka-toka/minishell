# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

void	fn(int sig)
{
	printf("i cautch a signal = %d", sig);
    write(1, "\n", 1);
//    exit(100);
}

int main()
{
    char arr1[] = "AAA";
    char arr2[] = "AA";
    char arr3[] = "A";
    char arr4[] = "AAAA";
    char arr5[] = "";
    char arr6[] = "AAAAA";

    printf("res = %d\n", ft_strcmp(arr1, arr2));
    printf("res = %d\n", ft_strcmp(arr1, arr3));
    printf("res = %d\n", ft_strcmp(arr1, arr4));
    printf("res = %d\n", ft_strcmp(arr1, arr5));
    printf("res = %d\n", ft_strcmp(arr1, arr6));

    printf("\n");

    printf("res = %d\n", ft_strcmp(arr2, arr1));
    printf("res = %d\n", ft_strcmp(arr2, arr2));
    printf("res = %d\n", ft_strcmp(arr2, arr3));
    printf("res = %d\n", ft_strcmp(arr2, arr4));
    printf("res = %d\n", ft_strcmp(arr2, arr5));
    printf("res = %d\n", ft_strcmp(arr2, arr6));

    printf("\n");
    printf("res = %d\n", ft_strcmp(arr3, arr1));
    printf("res = %d\n", ft_strcmp(arr3, arr2));
    printf("res = %d\n", ft_strcmp(arr3, arr3));
    printf("res = %d\n", ft_strcmp(arr3, arr4));
    printf("res = %d\n", ft_strcmp(arr3, arr5));
    printf("res = %d\n", ft_strcmp(arr3, arr6));

    return(0);
}