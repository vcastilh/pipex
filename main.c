/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:49:54 by vcastilh          #+#    #+#             */
/*   Updated: 2022/05/10 16:42:46 by coder            ###   ########.fr       */
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
		str[i] = NULL;
		i++;
	}
}
char	**get_cmd_argv(char *argv)
{
	char	**cmd_argv;

	cmd_argv = ft_split(argv, ' ');
	return (cmd_argv);
}

char	**get_bin_path(char **envp, char **cmd_argv)
{
	char	**bin_path;
	size_t	i;
	char	*tmp_bin_path;

	bin_path = ft_split(ft_getenv("PATH", envp), ':');
	i = 0;
	while (bin_path[i])
	{
		tmp_bin_path = bin_path[i];
		bin_path[i] = ft_strjoin(bin_path[i], "/");
		free(tmp_bin_path);
		tmp_bin_path = NULL;
		tmp_bin_path = bin_path[i];
		bin_path[i] = ft_strjoin(bin_path[i], *cmd_argv);
		free(tmp_bin_path);
		tmp_bin_path = NULL;
		i++;
	}
	return (bin_path);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	**bin_path;
	char	**cmd_argv;
	int		pid;
	int		pipe_fd[2];//read_end[0] write_end[1]
	int		fd[2];//fd[0] = file1   fd[1] = file2
	size_t	i;
	int		cmd_pos;

	if (argc != 5)
		return (1);
	cmd_pos = 1;
	while (++cmd_pos < argc - 1) 
	{
		if(pipe(pipe_fd) == -1)
			return (1);
		cmd_argv = get_cmd_argv(argv[cmd_pos]); //{"cat", NULL}; {"wc", NULL};
		bin_path = get_bin_path(envp, cmd_argv); // "/usr/bin/cat" ; {"cat", NULL};
		i = 0;
		while (bin_path[i] != NULL)
		{
			if (!(access(bin_path[i], F_OK | X_OK)))
			{
				pid = fork();
				if (pid < 0)
					return (1);
				if (pid == 0)
				{
					if (cmd_pos == 2)
					{
						fd[0] = open("file1.txt", O_RDONLY);//fd deve existir para o segundo comando tbm(segundo cmd precisa de input?)
						close(pipe_fd[0]);
						dup2(fd[0], STDIN_FILENO);
						dup2(pipe_fd[1], STDOUT_FILENO);
						close(pipe_fd[1]);
						if(execve(bin_path[i], cmd_argv, envp) == -1)
							return (1);
					}
					else if (cmd_pos == argc - 2)
					{
						fd[1] = open("file2.txt", O_RDWR | O_TRUNC | O_CREAT, 0664);
						close(pipe_fd[0]);
						close(pipe_fd[1]);
						dup2(fd[1], STDOUT_FILENO);
						if(execve(bin_path[i], cmd_argv, envp) == -1)
							return (1);
					}
					else
					{
						close(pipe_fd[0]);
						dup2(pipe_fd[1], STDOUT_FILENO);
						if(execve(bin_path[i], cmd_argv, envp) == -1)
							return (1);
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
		free_ptr(cmd_argv);
		free_ptr(bin_path);
	}
	return (0);
}
