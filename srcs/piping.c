/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierce <mpierce@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:07:05 by mpierce           #+#    #+#             */
/*   Updated: 2025/02/11 16:15:13 by mpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	do_pipe(t_pipex *pipex, int heredoc)
{
	int	i;

	if (pipe(pipex->pipex_fd) < 0)
		error_ret(pipex, "Pipex", EXIT_FAILURE);
	do_first_cmd(pipex->argv[1], pipex);
	next_pipe(pipex, 0);
	do_last_cmd(pipex->argv[pipex->cmd_count], pipex);
	close_fd(pipex);
	i = 2 + heredoc;
	while (i++ < pipex->argc)
		wait(NULL);
}

void	do_first_cmd(char *cmd, t_pipex *pipex)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (pid < 0)
		error_ret_noerrno(pipex, "Fork failure\n", EXIT_FAILURE);
	if (pid)
		return ;
	if (*cmd == 0)
		error_ret_noerrno(pipex, "Pipex: permission denied:\n", EXIT_FAILURE);
	open_infile(pipex);
	if (dup2(pipex->fd_in, 0) < 0 || dup2(pipex->pipex_fd[1], 1) < 0)
		error_ret(pipex, "Pipex", EXIT_FAILURE);
	close_fd(pipex);
	pipex->full_cmd = ft_quotesplit(cmd, 32);
	if (ft_strchr(cmd, '/'))
		cmd_path = pipex->full_cmd[0];
	else
		cmd_path = get_path(pipex, pipex->full_cmd[0], pipex->envp);
	execve(cmd_path, pipex->full_cmd, pipex->envp);
	error_ret(pipex, cmd, 127);
}

void	do_last_cmd(char *cmd, t_pipex *pipex)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (pid < 0)
		error_ret_noerrno(pipex, "Fork failure\n", EXIT_FAILURE);
	if (pid)
		return ;
	if (*cmd == 0)
		error_ret_noerrno(pipex, "Pipex: permission denied:\n", EXIT_FAILURE);
	open_outfile(pipex);
	if (dup2(pipex->prev_fd, 0) < 0 || dup2(pipex->fd_out, 1) < 0)
		error_ret(pipex, "Pipex", EXIT_FAILURE);
	close_fd(pipex);
	pipex->full_cmd = ft_quotesplit(cmd, 32);
	if (ft_strchr(cmd, '/'))
		cmd_path = pipex->full_cmd[0];
	else
		cmd_path = get_path(pipex, pipex->full_cmd[0], pipex->envp);
	execve(cmd_path, pipex->full_cmd, pipex->envp);
	error_ret(pipex, cmd, 127);
}
