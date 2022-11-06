/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:55:58 by malord            #+#    #+#             */
/*   Updated: 2022/11/06 13:15:00 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_command(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '\0')
	{
		write(2, strerror(EACCES), 17);
		write(2, ":\n", 2);
		exit (0);
	}
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			break ;
		i++;
		if (cmd[i] == '\0')
		{
			write(2, "command not found: \n", 20);
			exit (0);
		}
	}
}

int	check_envp(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0 && envp[i])
	{
		i++;
		if (envp[i] == NULL)
		{
			write(2, "No environment variables found\n", 27);
			exit(0);
		}
	}
	return (i);
}

void	free_paths(char **paths, int i)
{
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
}

char	*get_paths_command(char **envp, char *cmd)
{
	int		i;
	char	**paths;
	char	*cmd_path;
	char	*temp;

	i = check_envp(envp);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i++])
	{
		temp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin_free(temp, cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	i = 0;
	free_paths(paths, i);
	free(paths);
	return (NULL);
}
