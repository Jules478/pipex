/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierce <mpierce@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:06:11 by mpierce           #+#    #+#             */
/*   Updated: 2025/02/11 16:13:50 by mpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_all(t_pipex *pipex)
{
	free(pipex->argv);
}

void	error_ret(t_pipex *pipex, char *name, int ex_code)
{
	perror(name);
	close_fd(pipex);
	free(pipex->argv);
	if (pipex->full_cmd)
		free_array(&pipex->full_cmd);
	exit(ex_code);
}

void	error_ret_noerrno(t_pipex *pipex, char *name, int ex_code)
{
	write(2, name, ft_strlen(name));
	close_fd(pipex);
	free(pipex->argv);
	if (pipex->full_cmd)
		free_array(&pipex->full_cmd);
	exit(ex_code);
}

void	assign_to_struct(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int		i;

	i = 1;
	pipex->argc = argc - 1;
	pipex->envp = envp;
	pipex->out = pipex->argc - 1;
	pipex->cmd_count = argc - 3;
	pipex->fd_in = -1;
	pipex->fd_out = -1;
	pipex->pipex_fd[0] = -1;
	pipex->pipex_fd[1] = -1;
	pipex->prev_fd = -1;
	pipex->full_cmd = NULL;
	pipex->argv = malloc (argc * sizeof(char *));
	if (!pipex->argv)
		error_ret_noerrno(pipex, "Pipex malloc failure\n", EXIT_FAILURE);
	while (argv[i])
	{
		pipex->argv[i - 1] = argv[i];
		i++;
	}
}
