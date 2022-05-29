/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:49:54 by vcastilh          #+#    #+#             */
/*   Updated: 2022/05/29 19:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	check_argc(argc, argv, &data);
	open_files(argv, &data);
	data.cmd_pos = 1;
	if (pipe(data.pipe_fd) == -1)
		handle_exit(argv[0], ft_strdup(":Pipe error\n"), &data, 0);
	while (++data.cmd_pos < argc - 1)
	{
		get_data(&data, argv, envp);
		data.pid = fork();
		if (data.pid < 0)
			handle_exit(argv[0], ft_strdup(":Fork error\n"), &data, 1);
		else if (data.pid == 0)
			child_process(&data, argv, envp);
		waitpid(data.pid, &data.pid_status, 0);
		data.exit_status = (((data.pid_status) & 0xff00) >> 8);
		close(data.pipe_fd[1]);
		free_ptr(data.cmd_argv);
		free_ptr(data.bin_path);
		free(data.pathname);
	}
	close_fds(&data);
	return (data.exit_status);
}
