/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:45:26 by coder             #+#    #+#             */
/*   Updated: 2022/05/17 21:45:25 by coder            ###   ########.fr       */
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

char	*check_bin_acess(t_data *data)
{
	int	i;

	i = 0;
	while (data->bin_path[i] != NULL)
	{
		if (!(access(data->bin_path[i], F_OK | X_OK)))
		{
			return (data->bin_path[i]);
		}
		else
			i++;
	}
	
	return (NULL);

}

int	get_data(t_data *data, char **argv, char **envp)
{
	data->cmd_argv = get_cmd_argv(argv[data->cmd_pos]);
	if (data->cmd_argv)
	{
		data->bin_path = get_bin_path(envp, data->cmd_argv);
		if (data->bin_path)
		{
			data->pathname = ft_strdup(check_bin_acess(data));
			return (1);
		}
		else
		{
			write(2, "arquivo ou diretorio inextistente\n", 17);
			return (0);
		}
	}
	else
	{
		perror("invalid arg\n");
		return (0);
	}	
}
