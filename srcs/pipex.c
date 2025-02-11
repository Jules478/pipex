/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierce <mpierce@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:48:18 by mpierce           #+#    #+#             */
/*   Updated: 2025/02/06 17:52:11 by mpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_printf("./pipex <infile> <cmd1> <cmd2> <outfile>\n");
		exit(EXIT_FAILURE);
	}
	assign_to_struct(&pipex, argc, argv, envp);
	do_pipe(&pipex, 0);
	free_all(&pipex);
	return (0);
}
