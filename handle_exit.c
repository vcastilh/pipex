/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:02:12 by coder             #+#    #+#             */
/*   Updated: 2022/05/29 20:34:45 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_argc(int argc, char *argv[], t_data *data)
{
	if (argc != 5)
	{
		data->exit_status = 1;
		handle_exit(argv[0], ft_strdup(":Error: need 4 arguments\n"), data, 0);
	}
}

void	close_fds(t_data *data)
{
	close(data->pipe_fd[0]);
	if (data->fd[0] > 0)
		close(data->fd[0]);
	if (data->fd[1] > 0)
		close(data->fd[1]);
}

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

void	handle_exit(char *arg, char *msg, t_data *data, int is_get_data)
{
	write(2, arg, ft_strlen(arg));
	write(2, msg, ft_strlen(msg));
	free(msg);
	if (is_get_data)
	{
		free_ptr(data->cmd_argv);
		free_ptr(data->bin_path);
		free(data->pathname);
	}
	exit(data->exit_status);
}
