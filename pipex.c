/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:20:16 by ntenisha          #+#    #+#             */
/*   Updated: 2022/03/27 18:20:18 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int	fdin;

	fdin = open(argv[1], O_RDONLY, 0777);
	if (fdin == -1)
		error("Open fdin error");
	if (dup2(fd[1], 1) == -1)
		error("dup2 error1");
	if (dup2(fdin, 0) == -1)
		error("dup2 error2");
	close(fd[0]);
	close(fd[1]);
	close(fdin);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	fdout;

	fdout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout == -1)
		error("Open fdout error");
	if (dup2(fd[0], 0) == -1)
		error("dup2 error3");
	if (dup2(fdout, 1) == -1)
		error("dup2 error4");
	close(fd[1]);
	close(fd[0]);
	close(fdout);
	execute(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error("Pipe error");
		pid = fork();
		if (pid == -1)
			error("Fork error");
		if (pid == 0)
			child_process(argv, envp, fd);
		parent_process(argv, envp, fd);
		close(fd[0]);
		close(fd[1]);
	}
	else
		ft_putstr_fd("Bad arguments\n", 2);
	return (0);
}
