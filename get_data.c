/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:45:26 by coder             #+#    #+#             */
/*   Updated: 2022/05/13 17:49:55 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_cmd_argv(char *argv)
{
	char	**cmd_argv;
	int		i;
	char	*tmp_cmd;

	i = 0;
	cmd_argv = ft_split(argv, ' ');
	while (cmd_argv[i] != NULL)
	{
		if(*cmd_argv[i] == '\'')
		{
			tmp_cmd = cmd_argv[i];
			cmd_argv[i] = ft_strtrim(tmp_cmd, "\'");
			free(tmp_cmd);
			tmp_cmd = NULL;
			i++;		
		}
		else
			i++;	
	}
	tmp_cmd = NULL;
	return (cmd_argv);
}

char	**get_bin_path(char **envp, char **cmd_argv)
{
	char	**bin_path;
	size_t	i;
	char	*tmp_bin_path;

	bin_path = ft_split(ft_getenv("PATH", envp), ':');
	i = 0;
	while (bin_path[i])
	{
		tmp_bin_path = bin_path[i];
		bin_path[i] = ft_strjoin(bin_path[i], "/");
		free(tmp_bin_path);
		tmp_bin_path = NULL;
		tmp_bin_path = bin_path[i];
		bin_path[i] = ft_strjoin(bin_path[i], *cmd_argv);
		free(tmp_bin_path);
		tmp_bin_path = NULL;
		i++;
	}
	return (bin_path);
}
