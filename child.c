/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 01:59:22 by coder             #+#    #+#             */
/*   Updated: 2022/05/17 21:48:03 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

void	child_process(t_data *data, int argc, char *envp[])
{
	if (data->cmd_pos == 2)
	{
		data->fd[0] = open("file1.txt", O_RDONLY);//fd deve existir para o segundo comando tbm(segundo cmd precisa de input?)
		close(data->pipe_fd[0]);
		dup2(data->fd[0], STDIN_FILENO);
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[1]);
		if(execve(data->pathname, data->cmd_argv, envp) == -1)
		{
			perror("cmd failed");
		}
	}
	else if (data->cmd_pos == argc - 2)
	{
		data->fd[1] = open("file2.txt", O_RDWR | O_TRUNC | O_CREAT, 0664);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		dup2(data->fd[1], STDOUT_FILENO);
		if(execve(data->pathname, data->cmd_argv, envp) == -1)
		{
			perror("last cmd failed");
		}
	}
}
