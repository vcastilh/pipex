/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:49:54 by vcastilh          #+#    #+#             */
/*   Updated: 2022/05/14 02:36:31 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_ptr(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	size_t	i;
	t_data	data;

	data.cmd_pos = 1;
	while (++data.cmd_pos < argc - 1) 
	{
		if(pipe(data.pipe_fd) == -1)
			return (1);
		data.cmd_argv = get_cmd_argv(argv[data.cmd_pos]);
		data.bin_path = get_bin_path(envp, data.cmd_argv);
		i = 0;
		while (data.bin_path[i] != NULL)
		{
			if (!(access(data.bin_path[i], F_OK | X_OK)))
			{
				data.pid = fork();
				if (data.pid < 0)
					return (1);
				if (data.pid == 0)
				{
					child_process(&data, argc, i, envp);
				}
				waitpid(data.pid, NULL, 0);
				break;
			}
			i++;
		}
		close(data.pipe_fd[1]);
		dup2(data.pipe_fd[0], STDIN_FILENO);
		close(data.pipe_fd[0]);
		free_ptr(data.cmd_argv);
		free_ptr(data.bin_path);
	}
	return (0);
}
