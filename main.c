#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

int ft_strlen()

void ft_error(char *str)
{
    write(2, str, ft_strlen(str));
}

int argument_check(int ac, char **av)
{
    if (ac < 5 || 6 < ac)
        return (0);
}

int main(int ac, char **av)
{
    if (argument_check(ac, av) == 0)
        ft_error("Argument Error\n");
    else
    {

    } 
    return (0);
}
