/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierce <mpierce@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:07:05 by mpierce           #+#    #+#             */
/*   Updated: 2025/02/03 15:54:02 by mpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	do_pipe(t_pipex *pipex, int heredoc)
{
	int	i;

	if (pipe(pipex->pipex_fd) < 0)
		error_ret(pipex, "Pipex");
	if (heredoc)
		do_first_cmd_heredoc(pipex->argv[1], pipex->argv[2], pipex);
	else
		do_first_cmd(pipex->argv[1], pipex);
	next_pipe(pipex, 0);
	i = 2 + heredoc;
	while (i < pipex->cmd_count)
	{
		do_mid_cmd(pipex->argv[i], pipex);
		next_pipe(pipex, i + 1 >= pipex->cmd_count);
		i++;
	}
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
		error_ret(pipex, "Fork failure\n");
	if (pid)
		return ;
	open_infile(pipex);
	if (dup2(pipex->fd_in, 0) < 0 || dup2(pipex->pipex_fd[1], 1) < 0)
	{
		error_ret(pipex, "Pipex");
	}
	close_fd(pipex);
	pipex->full_cmd = ft_quotesplit(cmd, 32);
	if (*cmd == '.' || *cmd == '/')
		cmd_path = pipex->full_cmd[0];
	else
		cmd_path = get_path(pipex->full_cmd[0], pipex->envp);
	execve(cmd_path, pipex->full_cmd, pipex->envp);
	error_ret(pipex, cmd);
}

void	do_mid_cmd(char	*cmd, t_pipex *pipex)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (pid < 0)
		error_ret(pipex, "Fork failure\n");
	if (pid)
		return ;
	if (dup2(pipex->prev_fd, 0) < 0 || dup2(pipex->pipex_fd[1], 1) < 0)
	{
		error_ret(pipex, "Pipex");
	}
	close_fd(pipex);
	if (*cmd == '.' || *cmd == '/')
		cmd_path = cmd;
	else
	{
		pipex->full_cmd = ft_quotesplit(cmd, 32);
		cmd_path = get_path(pipex->full_cmd[0], pipex->envp);
	}
	execve(cmd_path, pipex->full_cmd, pipex->envp);
	error_ret(pipex, cmd);
}

void	do_last_cmd(char *cmd, t_pipex *pipex)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (pid < 0)
		error_ret(pipex, "Fork failure\n");
	if (pid)
		return ;
	open_outfile(pipex);
	if (dup2(pipex->prev_fd, 0) < 0 || dup2(pipex->fd_out, 1) < 0)
	{
		error_ret(pipex, "Pipex");
	}
	close_fd(pipex);
	if (*cmd == '.' || *cmd == '/')
		cmd_path = cmd;
	else
	{
		pipex->full_cmd = ft_quotesplit(cmd, 32);
		cmd_path = get_path(pipex->full_cmd[0], pipex->envp);
	}
	execve(cmd_path, pipex->full_cmd, pipex->envp);
	error_ret(pipex, cmd);
}

void	do_first_cmd_heredoc(char *lim, char *cmd, t_pipex *pipex)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (pid < 0)
		error_ret(pipex, "Fork failure\n");
	if (pid)
		return ;
	open_heredoc(pipex, lim);
	if (dup2(pipex->fd_in, 0) < 0 || dup2(pipex->pipex_fd[1], 1) < 0)
	{
		error_ret(pipex, "Pipex");
	}
	close_fd(pipex);
	if (*cmd == '.' || *cmd == '/')
		cmd_path = cmd;
	else
	{
		pipex->full_cmd = ft_quotesplit(cmd, 32);
		cmd_path = get_path(pipex->full_cmd[0], pipex->envp);
	}
	execve(cmd_path, pipex->full_cmd, pipex->envp);
	error_ret(pipex, cmd);
}
