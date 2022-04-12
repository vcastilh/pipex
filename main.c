/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastilh <vcastilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:49:54 by vcastilh          #+#    #+#             */
/*   Updated: 2022/04/11 16:27:29 by vcastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

extern char** environ;

int	main(void)
{
	char	*cmd_path = "/usr/bin/ls";
	char	*cmd_args[] = {"ls", "-l", "-a", NULL};
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		printf("BABY\n");
		if(execve(cmd_path, cmd_args, environ) == -1)
			return (1);
	}
	else if (pid > 0)
	{
		waitpid(-1, NULL, 0);
		printf("MAMA\n");
		return (0);
	}
	return (1);
}
