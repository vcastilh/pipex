/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 01:59:22 by coder             #+#    #+#             */
/*   Updated: 2022/05/28 18:04:56 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_data *data, char *argv[], char *envp[])
{
	if (data->cmd_pos == 2)
	{
		close(data->pipe_fd[0]);
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		//close(data->pipe_fd[1]);
		if(dup2(data->fd[0], STDIN_FILENO) == -1)
		{
			strerror(2);
		}
		else
		{
			close(data->fd[0]);
			if (execve(data->pathname, data->cmd_argv, envp) == -1)
			{
				handle_exit(data->pathname, ft_strdup(":command not found\n"),
					data, 1);
			}
		}
	}
	else
	{
		data->fd[1] = open_file(argv[4],  O_TRUNC | O_RDWR | O_CREAT, data, 0);
		dup2(data->pipe_fd[0], STDIN_FILENO);
		//close(data->pipe_fd[0]);
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[1]);
		if (execve(data->pathname, data->cmd_argv, envp) == -1)
		{
			handle_exit(data->pathname, ft_strdup(":command not found\n"),
				data, 1);
		}
	}
}
