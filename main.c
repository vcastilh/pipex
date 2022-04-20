/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastilh <vcastilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:49:54 by vcastilh          #+#    #+#             */
/*   Updated: 2022/04/20 18:41:55 by vcastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

extern char** environ;

int	main(void)
{
	char	*cmd_path = "/usr/bin/cat";
	char	*cmd_args[] = {"cat", "-E", NULL};
	char	*cmd2_path = "/usr/bin/grep";
	char	*cmd2_args[] = {"grep", "love", NULL};
	int		pid;
	int		pipe_fd[2];
	int		fd[2];

	if(pipe(pipe_fd) == -1)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		fd[0] = open("file1.txt", O_RDONLY);
		printf("BABY\n");
		dup2(fd[0], 0);
		dup2(pipe_fd[1], 1);
		close(fd[0]);
		if(execve(cmd_path, cmd_args, environ) == -1)
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
		if(execve(cmd2_path, cmd2_args, environ) == -1)
			return (1);
	}
	return (1);
}
