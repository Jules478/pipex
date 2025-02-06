/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierce <mpierce@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:48:18 by mpierce           #+#    #+#             */
/*   Updated: 2025/02/03 14:08:40 by mpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
		if (!access(".temp", F_OK))
			unlink(".temp");
	}
	else
		do_pipe(&pipex, 0);
	free_all(&pipex);
	return (0);
}
