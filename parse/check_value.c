#include "../header/object.h"
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

int split_count(char **split)
{
    int i;

    i = 0;
    while(split[i])
        i++;
    return i;
}

void printf_error(char *msg)
{
    printf("%s",msg);
    exit(1);
}

int is_valid_double(char *str)
{
    int i;
    int dot_count;

    i = 0;
    dot_count = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (str[i] == '.')
        {
            dot_count++;
            if (dot_count > 1) 
                return (0);
        }
        else if (!ft_isdigit(str[i])) 
        {
            if (str[i] != '\n') 
                return (0);
        }
        i++;
    }
    return (1);
}

double parse_double(char *str)
{
    if (!is_valid_double(str))
    {
        printf("Error: Invalid number format: %s\n", str);
        exit(1);
    }
    return (ft_atod(str));
}
