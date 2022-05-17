/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastilh <vcastilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 00:23:02 by vcastilh          #+#    #+#             */
/*   Updated: 2022/05/17 21:46:26 by coder            ###   ########.fr       */
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

typedef struct s_data
{
	char	**bin_path;
	char	**cmd_argv;
	int		cmd_pos;
	char	*pathname;
	int		pid;
	int		pipe_fd[2];
	int		fd[2];
}	t_data;


int		get_data(t_data *data, char *argv[], char *envp[]);
char	**get_cmd_argv(char *argv);
char	**get_bin_path(char **envp, char **cmd_argv);
void	child_process(t_data *data, int argc, char *envp[]);
#endif
