/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 09:46:10 by malord            #+#    #+#             */
/*   Updated: 2022/08/02 10:15:55 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(void)
{
	int		pipefds[2];
	char	*pin;
	char	*buffer;
	pid_t	pid;

	if (pipe(pipefds) == -1)
	{
		perror("pipe");
		exit(0);
	}
	pid = fork();
	if (pid == 0) // child process = 0, parent process > 0
	{
		pin = "69696969";
		close (pipefds[0]);
		write (pipefds[1], pin, ft_strlen(pin));
		printf("Generating PIN in child and sending to parent ...\n");
		exit(0);
	}
	buffer = ft_calloc(sizeof(char), 8);
	if (pid > 0) // parent process! 
	{
		waitpid(pid, NULL, 0);
		close (pipefds[1]);
		read(pipefds[0], buffer, 8);
		close (pipefds[0]);
		printf("Parent received pin '%s'\n", buffer);
	}
	return (0);
}
