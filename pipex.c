/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 08:57:51 by malord            #+#    #+#             */
/*   Updated: 2022/08/16 11:45:45 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_command(char **envp, char *arg)
{
	char	*cmd_path;
	char	**cmd;
	int		i;

	i = -1;
	cmd = ft_split(arg, ' ');
	cmd_path = get_paths_command(envp, cmd[0]);
	if (!cmd_path)
	{
		write(2, "command not found: ", 20);
		while (cmd[++i])
		{
			write(2, cmd[i], ft_strlen(cmd[i]));
			write(2, " ", 1);
			free(cmd[i]);
		}
		free(cmd);
		write(2, "\n", 1);
		exit (1);
	}
	execve(cmd_path, cmd, envp);
	exit(1);

}

void	do_child(int *fd, char **envp, char *file, char **av)
{
	int		fd2;

	fd2 = open(file, O_RDONLY, 0777);
	if (fd2 == -1)
	{
		printf("%s: %s\n", strerror(ENOENT), file);
		exit (1);
	}
	dup2(fd[1], 1);
	dup2(fd2, 0);
	close(fd[0]);
	check_command(av[2]);
	exec_command(envp, av[2]);
	close(fd2);
}

void	do_parent(int *fd, char **envp, char *file, char **av)
{
	int		fd2;

	fd2 = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd2 == -1)
	{
		printf("%s: %s\n", strerror(EBADF), file);
		exit (1);
	}
	dup2(fd[0], 0);
	dup2(fd2, 1);
	close(fd[1]);
	check_command(av[3]);
	exec_command(envp, av[3]);
	close(fd2);
}

int	main(int argc, char **argv, char **envp)
{
	int	pid;
	int	fd[2];

	if (argc == 5)
	{
		if (pipe(fd) == -1)
		{
			perror(strerror(EPIPE));
			return (1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror(strerror(ECHILD));
			return (1);
		}
		if (pid == 0)
			do_child(fd, envp, argv[1], argv);
		do_parent(fd, envp, argv[4], argv);
	}
	else
		write(2, "Wrong number of arguments\n", 27);
	return (0);
}
