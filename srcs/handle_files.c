/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierce <mpierce@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:02:52 by mpierce           #+#    #+#             */
/*   Updated: 2025/02/10 17:56:02 by mpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_infile(t_pipex *pipex)
{
	int ex_code;

	pipex->fd_in = open(pipex->argv[0], O_RDONLY, 0644);
	if (pipex->fd_in == -1)
	{
		if (errno == ENOENT)
			ex_code = 127;
		else if (errno == EACCES)
			ex_code = 126;
		else
			ex_code = 1;
		close_fd(pipex);
		error_ret(pipex, pipex->argv[0], ex_code);
	}
}

void	open_outfile(t_pipex *pipex)
{
	int ex_code;
	
	pipex->fd_out = open(pipex->argv[pipex->out], O_WRONLY \
		| O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_out == -1)
	{
		if (errno == ENOENT)
			ex_code = 127;
		else if (errno == EACCES)
			ex_code = 126;
		else
			ex_code = 1;
		close_fd(pipex);
		error_ret(pipex, pipex->argv[pipex->out], ex_code);
	}
}

void	close_fd(t_pipex *pipex)
{
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	if (pipex->fd_out != -1)
		close(pipex->fd_out);
	if (pipex->pipex_fd[0] != -1)
		close(pipex->pipex_fd[0]);
	if (pipex->pipex_fd[1] != -1)
		close(pipex->pipex_fd[1]);
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
}

void	next_pipe(t_pipex *pipex, int check)
{
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	close(pipex->pipex_fd[1]);
	pipex->pipex_fd[1] = -1;
	pipex->prev_fd = pipex->pipex_fd[0];
	pipex->pipex_fd[0] = -1;
	if (check)
		return ;
	if (pipe(pipex->pipex_fd) < 0)
		error_ret(pipex, "Pipex", EXIT_FAILURE);
}
