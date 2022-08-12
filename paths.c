/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:55:58 by malord            #+#    #+#             */
/*   Updated: 2022/08/04 10:56:01 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_check_cmd(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '\0')
	{
		write(2, strerror(13), 17);
		write(2, ":\n", 2);
		exit (1);
	}
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			break ;
		i++;
		if (cmd[i] == '\0')
		{
			write(2, "command not found: \n", 20);
			exit (1);
		}
	}
}

int	ft_check_envp(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0 && envp[i])
	{
		i++;
		if (envp[i] == NULL)
		{
			write(2, "Environnement pas trouvé\n", 27);
			exit(1);
		}
	}
	return (i);
}

char	*ft_retrieve_paths_n_cmd(char **envp, char *cmd)
{
	int		i;
	char	**paths;
	char	*cmd_path;
	char	*temp;

	i = ft_check_envp(envp);
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		free (temp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}
