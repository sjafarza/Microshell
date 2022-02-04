#include"microshell.h"

int	ft_strlen(char *s)
{
	int	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_fatal(void)
{
	write(2, "error: fatal\n",14);
	exit(EXIT_FAILURE);
}

int	get_pos_of_c(int ac, char **av, char c)
{
	int	i = -1;
	while(++i < ac)
		if (av[i][0] == c)
			return (i -1);
	return (ac - 1);
}

int chang_path(char *path)
{
	int ret;
	if (!path)
		return (-1);
	ret = chdir(path);
	if (ret < 0)
		return (-1);
	return (ret);
}

int	ft_cd(char **cur)
{
	int ret;
	if (cur[1] == NULL || cur[2] != NULL)
	{
		write(2, "error: cd: bad arguments\n", 26);
		return (0);
	}
	ret = chang_path(cur[1]);
	if (ret < -1)
	{
		write(2, "error: cd: cannot change directory to ", 39);
		write(2, cur[1], ft_strlen(cur[1]));
		write(2, "\n", 2);
	}
	return (ret);
}
		
void	main_func(char **cur_pip,int  *old_pip[], t_shell  shell, char  **env)
{
	int	ret;
	pid_t	cpid;
	int	new_pip[2];

	ret = 0;
	cpid = 0;
	if (strcmp(cur_pip[0], "cd") == 0)
		ret = ft_cd(cur_pip);
	else
	{
		if (shell.next)
			if (pipe(new_pip) < 0)
				ft_fatal();
		cpid = fork();
		if (cpid < 0)
			ft_fatal();
		else if (cpid == 0)
		{
			if (shell.prev)
			{
				if (dup2(*old_pip[0] , 0) < 0)
					ft_fatal();
				close(*old_pip[0]);
				close(*old_pip[1]);
			}
			if (shell.next)
			{
				close(new_pip[0]);
				if (dup2(new_pip[1] ,1 ) < 0)
					ft_fatal();
				close(new_pip[1]);
			}
			ret = execve(cur_pip[0], cur_pip, env);
			if (ret == -1)
			{
				write(2, "error: cannot execute ", 23);
				write(2, cur_pip[0], ft_strlen(cur_pip[0]));
				write(2, "\n", 1);
			}
			exit(ret);
		}
		else
		{
			if (shell.prev)
			{
				close(*old_pip[0]);
				close(*old_pip[1]);
			}
			if (shell.next)
			{
				 *old_pip[0] = new_pip[0];
				 *old_pip[1] = new_pip[1];
			}
			waitpid(cpid, NULL, 0);
		}
	}
}

void	get_pip(t_com com,  char **env)
{
	int	pos;
	int	pip_start;
	int	i;
	t_shell	shell;
	char	**cur_pip;
	int	*old_pip[2];

	pos = 0;
	pip_start = com.start;
	shell.prev = 0;
	shell.next = 1;
	old_pip[0] = malloc(sizeof(int));
	old_pip[1] = malloc(sizeof(int));
	if(!old_pip[0] || !old_pip[1])
		ft_fatal();
	while (pos < com.end)
	{
		pos = pip_start + get_pos_of_c(com.end - pip_start + 1, com.com + pip_start, '|');
		if (pos > com.end)
			break ;
		if (pip_start > com.start)
			shell.prev = 1;
		if (pos == com.end)
			shell.next = 0;
		cur_pip = malloc(sizeof(char *) * (pos - pip_start + 2));
		if (!cur_pip)
			ft_fatal();
		i = -1;
		while (++i < (pos - pip_start + 1))
			cur_pip[i] = com.com[pip_start + i];
		cur_pip[i] = NULL;
		main_func(cur_pip, old_pip, shell, env);
		pip_start = pos + 2;
		free(cur_pip);
	}
	free(old_pip[0]);
	free(old_pip[1]);
}

int	main(int ac, char **av, char **env)
{
	int	pos = 0;
	int	start = 1;
	t_com	com;

	com.com = av;
	while (pos < (ac -1))
	{
		pos = start + get_pos_of_c(ac - start, av + start , ';');
		com.start = start;
		com.end = pos;
		if (start <= pos)
			get_pip(com, env);
		start = pos + 2;
	}
	exit(EXIT_SUCCESS);
}
