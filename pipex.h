/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastilh <vcastilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 00:23:02 by vcastilh          #+#    #+#             */
/*   Updated: 2022/05/29 19:43:25 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
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
	int		pid_status;
	int		pipe_fd[2];
	int		fd[2];
	int		exit_status;
}	t_data;

void	get_data(t_data *data, char *argv[], char *envp[]);
char	**get_cmd_argv(char *argv);
char	**get_bin_path(char **envp, char **cmd_argv);
void	child_process(t_data *data, char *argv[], char *envp[]);
void	handle_exit(char *arg, char *msg, t_data *data, int is_getting_data);
void	open_files(char *argv[], t_data *data);
void	free_ptr(char **str);
void	first_cmd(t_data *data, char *envp[]);
void	second_cmd(t_data *data, char *argv[], char *envp[]);
void	close_fds(t_data *data);
void	check_argc(int argc, char *argv[], t_data *data);
#endif
