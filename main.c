/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:49:54 by vcastilh          #+#    #+#             */
/*   Updated: 2022/05/09 19:33:26 by coder            ###   ########.fr       */
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
		while (bin_path[i] != NULL)
		{
			if (!(access(bin_path[i], F_OK | X_OK)))
			{
				fd[0] = open("file1.txt", O_RDONLY);//E se não existir,fd deve existir para o segundo comando tbm(segundo cmd precisa de input?)
				printf("BABY\n");
				dup2(fd[0], STDIN_FILENO);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(fd[0]);
				if(execve(bin_path[i], cmd_argv, envp) == -1)
					return (1);
			}
			i++;
		}
		printf ("-bash: %s: command not found", *cmd_argv);
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
		free_ptr(bin_path);
		free_ptr(cmd_argv);
		cmd_argv = get_cmd_argv(argv[3]);
		bin_path = get_bin_path(envp, cmd_argv); 
		while (bin_path[i] != NULL)
		{
			if (!(access(bin_path[i], F_OK | X_OK)))
			{
				fd[0] = open("file1.txt", O_RDONLY);
				printf("BABY\n");
				dup2(fd[0], 0);
				dup2(pipe_fd[1], 1);
				close(fd[0]);
				if(execve(bin_path[i], cmd_argv, envp) == -1)
					return (1);
			}
			i++;
		}
	}
	return (1);
}
