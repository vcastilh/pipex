/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:02:12 by coder             #+#    #+#             */
/*   Updated: 2022/05/25 13:05:07 by coder            ###   ########.fr       */
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
	exit(1);
}
