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
    char arr4[] = "BA";
    char arr5[] = "С";
    char arr6[] = "D";

    printf("res = %d\n", ft_strncmp(arr1, arr2, 20));
    printf("res = %d\n", ft_strncmp(arr1, arr3, 20));
    printf("res = %d\n", ft_strncmp(arr1, arr4, 20));
    printf("res = %d\n", ft_strncmp(arr1, arr5, 20));
    printf("res = %d\n", ft_strncmp(arr1, arr6, 20));

    printf("\n");

    printf("res = %d\n", ft_strncmp(arr2, arr1, 20));
    printf("res = %d\n", ft_strncmp(arr2, arr2, 20));
    printf("res = %d\n", ft_strncmp(arr2, arr3, 20));
    printf("res = %d\n", ft_strncmp(arr2, arr4, 20));
    printf("res = %d\n", ft_strncmp(arr2, arr5, 20));
    printf("res = %d\n", ft_strncmp(arr2, arr6, 20));

    printf("\n");
    printf("res = %d\n", ft_strncmp(arr3, arr1, 20));
    printf("res = %d\n", ft_strncmp(arr3, arr2, 20));
    printf("res = %d\n", ft_strncmp(arr3, arr3, 20));
    printf("res = %d\n", ft_strncmp(arr3, arr4, 20));
    printf("res = %d\n", ft_strncmp(arr3, arr5, 20));
    printf("res = %d\n", ft_strncmp(arr3, arr6, 20));

    return(0);
}