/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierce <mpierce@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:45:47 by mpierce           #+#    #+#             */
/*   Updated: 2025/02/03 15:41:12 by mpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*find_path(char *cmd, char **envp)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		path = ft_substr(envp[i], 0, j);
		if (!ft_strcmp(path, cmd))
		{
			free(path);
			return (envp[i] + j + 1);
		}
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	*exe;
	char	**full_path;
	char	*part_path;
	char	**full_cmd;

	i = -1;
	full_path = ft_quotesplit(find_path("PATH", envp), ':');
	full_cmd = ft_quotesplit(cmd, 32);
	while (full_path[++i])
	{
		part_path = ft_strjoin(full_path[i], "/");
		exe = ft_strjoin(part_path, full_cmd[0]);
		free(part_path);
		if (!access(exe, F_OK | X_OK))
		{
			free_array(&full_cmd);
			return (exe);
		}
		free(exe);
	}
	free_array(&full_path);
	free_array(&full_cmd);
	return (cmd);
}
