/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:49:54 by vcastilh          #+#    #+#             */
/*   Updated: 2022/05/13 06:42:32 by coder            ###   ########.fr       */
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
	int		pid;
	int		pipe_fd[2];//read_end[0] write_end[1]
	int		fd[2];//fd[0] = file1   fd[1] = file2
	size_t	i;
	t_data	data;

	data.cmd_pos = 1;
	while (++data.cmd_pos < argc - 1) 
	{
		if(pipe(pipe_fd) == -1)
			return (1);
		data.cmd_argv = get_cmd_argv(argv[data.cmd_pos]); //{"cat", NULL}; {"wc", NULL};
		data.bin_path = get_bin_path(envp, data.cmd_argv); // "/usr/bin/cat" ; {"cat", NULL};
		i = 0;
		while (data.bin_path[i] != NULL)
		{
			if (!(access(data.bin_path[i], F_OK | X_OK)))
			{
				pid = fork();
				if (pid < 0)
					return (1);
				if (pid == 0)
				{
					if (data.cmd_pos == 2)
					{
						fd[0] = open("file1.txt", O_RDONLY);//fd deve existir para o segundo comando tbm(segundo cmd precisa de input?)
						close(pipe_fd[0]);
						dup2(fd[0], STDIN_FILENO);
						dup2(pipe_fd[1], STDOUT_FILENO);
						close(pipe_fd[1]);
						if(execve(data.bin_path[i], data.cmd_argv, envp) == -1)
						{
							perror("cmd failed");
							return (1);
						}
					}
					else if (data.cmd_pos == argc - 2)
					{
						fd[1] = open("file2.txt", O_RDWR | O_TRUNC | O_CREAT, 0664);
						close(pipe_fd[0]);
						close(pipe_fd[1]);
						dup2(fd[1], STDOUT_FILENO);
						if(execve(data.bin_path[i], data.cmd_argv, envp) == -1)
						{
							perror("last cmd failed");
							return (1);
						}
					}
					else
					{
						close(pipe_fd[0]);
						dup2(pipe_fd[1], STDOUT_FILENO);
						if(execve(data.bin_path[i], data.cmd_argv, envp) == -1)
						{
							perror("else cmd failed");
							return (1);
						}
					}
				}
				waitpid(pid, NULL, 0);
				break;
			}
			i++;
		}
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		free_ptr(data.cmd_argv);
		free_ptr(data.bin_path);
	}
	return (0);
}
