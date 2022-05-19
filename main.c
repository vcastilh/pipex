/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:49:54 by vcastilh          #+#    #+#             */
/*   Updated: 2022/05/18 20:10:26 by coder            ###   ########.fr       */
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
	t_data	data;

	data.cmd_pos = 1;
	while (++data.cmd_pos < argc - 1) 
	{
		if(pipe(data.pipe_fd) == -1)
			perror("pipe error\n");
		get_data(&data, argv, envp);
		data.pid = fork();
		if (data.pid < 0)
			perror("fork error\n");
		else if (data.pid == 0)
			child_process(&data, argv, envp);
		waitpid(data.pid, NULL, 0);
		close(data.pipe_fd[1]);
		dup2(data.pipe_fd[0], STDIN_FILENO);
		close(data.pipe_fd[0]);
		free_ptr(data.cmd_argv);
		free_ptr(data.bin_path);
		free(data.pathname);
	}
	return (0);
}
