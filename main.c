#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *ln;
    int     ln_count;

    fd = open("text.txt", 0);
    if (fd == -1)
    {
        printf("Error: Could not open file\n");
        return (1);
    }
    ln_count = 1;
    while (1)
    {
        ln = get_next_line(fd);
        if (ln == NULL)
            break;
        printf("Line %d: %s", ln_count, ln);
        if (ln[0] != '\0' && ln[ft_strlen(ln) - 1] != '\n')
            printf("\n");
        free(ln);
        ln_count++;
    }
    close(fd);
    return (0);
}