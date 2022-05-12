/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastilh <vcastilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 00:23:02 by vcastilh          #+#    #+#             */
/*   Updated: 2022/05/12 05:56:12 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "libft.h"
char	**get_cmd_argv(char *argv);
char	**get_bin_path(char **envp, char **cmd_argv);
typedef struct s_data
{
	char	**bin_path;
	char	**cmd_argv;
	int		cmd_pos;
}	t_data;
#endif
