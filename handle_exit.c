/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:02:12 by coder             #+#    #+#             */
/*   Updated: 2022/05/18 20:06:59 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_exit(char *arg, char *msg, t_data *data, int code_error)
{
	printf("%s: %s\n", arg, msg);
	free(msg);
	free_ptr(data->cmd_argv);
	free_ptr(data->bin_path);
	free(data->pathname);
	exit(code_error);
}
