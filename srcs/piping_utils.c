/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierce <mpierce@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:45:47 by mpierce           #+#    #+#             */
/*   Updated: 2025/02/06 17:12:13 by mpierce          ###   ########.fr       */
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

char	*get_path(t_pipex *pipex, char *cmd, char **envp)
{
	int		i;
	char	*exe;
	char	**full_path;
	char	*part_path;

	i = -1;
	full_path = ft_quotesplit(find_path("PATH", envp), ':');
	while (full_path[++i])
	{
		part_path = ft_strjoin(full_path[i], "/");
		exe = ft_strjoin(part_path, pipex->full_cmd[0]);
		free(part_path);
		if (!access(exe, F_OK | X_OK))
			return (exe);
		free(exe);
	}
	free_array(&full_path);
	return (cmd);
}
