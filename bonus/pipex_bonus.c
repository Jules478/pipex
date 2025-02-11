/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierce <mpierce@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:48:18 by mpierce           #+#    #+#             */
/*   Updated: 2025/02/11 16:11:17 by mpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	do_pipe(t_pipex *pipex, int heredoc)
{
	int	i;

	if (pipe(pipex->pipex_fd) < 0)
		error_ret(pipex, "Pipex", EXIT_FAILURE);
	if (heredoc)
		open_heredoc(pipex, pipex->argv[1]);
	else
		do_first_cmd(pipex->argv[1], pipex);
	next_pipe(pipex, 0);
	i = 2;
	while (i < pipex->cmd_count)
	{
		do_mid_cmd(pipex->argv[i], pipex);
		next_pipe(pipex, i + 1 >= pipex->cmd_count);
		i++;
	}
	if (heredoc)
		do_last_cmd_heredoc(pipex->argv[pipex->cmd_count], pipex);
	else
		do_last_cmd(pipex->argv[pipex->cmd_count], pipex);
	close_fd(pipex);
	i = 2 + heredoc;
	while (i++ < pipex->argc)
		wait(NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
	{
		ft_printf("./pipex <infile> <cmd1> <cmd2> ... <cmdn> <outfile>\n");
		exit(EXIT_FAILURE);
	}
	assign_to_struct(&pipex, argc, argv, envp);
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		if (argc < 6)
		{
			ft_printf("./pipex here_doc <lim> <cmd1> <cmd2> ... <cmdn> \
			<outfile>\n");
			free_all(&pipex);
			exit(EXIT_FAILURE);
		}
		do_pipe(&pipex, 1);
	}
	else
		do_pipe(&pipex, 0);
	free_all(&pipex);
	return (0);
}
