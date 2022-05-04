/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:49:54 by vcastilh          #+#    #+#             */
/*   Updated: 2022/05/04 04:24:07 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	char	*cmd_path = "/usr/bin/cat";
	char	*cmd_args[] = {"cat", NULL};
	char	*cmd2_path = "/usr/bin/wc";
	char	*cmd2_args[] = {"wc", NULL};
	char	**bin_path;
	char	**cmd_argv;
	int		pid;
	int		pipe_fd[2];
	int		fd[2];
	size_t	i;

	if (argc != 5)
		return (1);
	if(pipe(pipe_fd) == -1)
		return (1);
	cmd_argv = get_cmd_argv(argv[2]);
	bin_path = get_bin_path(envp, cmd_argv); 
	pid = fork();
	if (pid == 0)
	{
		fd[0] = open("file1.txt", O_RDONLY);
		printf("BABY\n");
		dup2(fd[0], 0);
		dup2(pipe_fd[1], 1);
		close(fd[0]);
		if(execve(cmd_path, cmd_args, envp) == -1)
			return (1);
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		printf("MAMA\n");
		close(pipe_fd[1]);
		fd[1] = open("file2.txt", O_RDWR | O_TRUNC | O_CREAT, 0664);
		if (fd[1] == -1)
			return (1);
		dup2(pipe_fd[0], 0);
		dup2(fd[1], 1);
		i = 0;
		while (bin_path[i])
		{
			free(bin_path[i]);
			bin_path[i] = NULL;
			i++;
		}
		if(execve(cmd2_path, cmd2_args, envp) == -1)
			return (1);
	}
	return (1);
}
