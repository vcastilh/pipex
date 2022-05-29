/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 01:59:22 by coder             #+#    #+#             */
/*   Updated: 2022/05/29 20:05:26 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_cmd(t_data *data, char *envp[])
{
	close(data->pipe_fd[0]);
	dup2(data->pipe_fd[1], STDOUT_FILENO);
	if (dup2(data->fd[0], STDIN_FILENO) != -1)
	{
		if (*data->pathname)
		{
			close(data->fd[0]);
			execve(data->pathname, data->cmd_argv, envp);
		}
		else
		{
			data->exit_status = 127;
			handle_exit(*data->cmd_argv,
				ft_strdup(": command not found\n"), data, 1);
		}
	}
	else
	{
		free_ptr(data->cmd_argv);
		free_ptr(data->bin_path);
		free(data->pathname);
		data->exit_status = 1;
		exit(data->exit_status);
	}
}

void	second_cmd(t_data *data, char *argv[], char *envp[])
{
	dup2(data->pipe_fd[0], STDIN_FILENO);
	if (dup2(data->fd[1], STDOUT_FILENO) != -1)
	{
		if (*data->pathname)
		{
			close(data->fd[1]);
			execve(data->pathname, data->cmd_argv, envp);
		}
		else
		{
			data->exit_status = 127;
			handle_exit(*data->cmd_argv,
				ft_strdup(": command not found\n"), data, 1);
		}
	}
	else
	{
		data->exit_status = 1;
		handle_exit(argv[4],
			ft_strdup("Failed to create file\n"), data, 1);
	}
}

void	child_process(t_data *data, char *argv[], char *envp[])
{
	if (data->cmd_pos == 2)
		first_cmd(data, envp);
	else
		second_cmd(data, argv, envp);
}
