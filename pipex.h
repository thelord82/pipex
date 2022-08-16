/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 10:39:45 by malord            #+#    #+#             */
/*   Updated: 2022/08/15 19:18:14 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/types.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "sys/errno.h"

void	check_command(char *cmd);
char	*get_command_path(char **envp, char *cmd);
#endif