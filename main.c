/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:49:54 by vcastilh          #+#    #+#             */
/*   Updated: 2022/05/27 20:28:11 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	if (argc != 5)
		handle_exit(argv[0], ft_strdup(":Error: need 4 arguments\n"), &data, 0);
	data.fd[0] = open_file(argv[1], F_OK, &data, 0);
	data.cmd_pos = 1;
	while (++data.cmd_pos < argc - 1)
	{
		if (pipe(data.pipe_fd) == -1)
			handle_exit(argv[0], ft_strdup(":Pipe error\n"), &data, 0);
		get_data(&data, argv, envp);
		data.pid = fork();
		if (data.pid < 0)
			handle_exit(argv[0], ft_strdup(":Fork error\n"), &data, 1);
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
	close(data.fd[1]);
	return (0);
}
