/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 01:59:22 by coder             #+#    #+#             */
/*   Updated: 2022/05/27 14:48:16 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_data *data, char *argv[], char *envp[])
{
	if (data->cmd_pos == 2)
	{
		close(data->pipe_fd[0]);
		dup2(data->fd[0], STDIN_FILENO);
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[1]);
		if (execve(data->pathname, data->cmd_argv, envp) == -1)
		{
			handle_exit(data->pathname, ft_strdup(":command not found\n"),
				data, 1);
		}
	}
	else
	{
		data->fd[1] = open_file(argv[4], O_RDWR | O_TRUNC | O_CREAT, data, 1);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		dup2(data->fd[1], STDOUT_FILENO);
		if (execve(data->pathname, data->cmd_argv, envp) == -1)
		{
			handle_exit(data->pathname, ft_strdup(":command not found\n"),
				data, 1);
		}
	}
}
