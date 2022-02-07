#ifndef MICROSHELL_H
# define MICROSHELL_H

# include<unistd.h>
# include<stdlib.h>
# include<string.h>
# include<sys/wait.h>
# include<dirent.h>
# include<stdio.h>

typedef struct s_com
{
        char    **com;
        int     end;
        int     start;
} t_com;

typedef struct s_shell
{
        int     prev;
        int     next;
} t_shell;

#endif
