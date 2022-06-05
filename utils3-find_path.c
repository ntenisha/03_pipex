/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3-find_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:20:46 by ntenisha          #+#    #+#             */
/*   Updated: 2022/03/27 18:40:45 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		i++;
	while (i > 0)
	{
		free(paths[i - 1]);
		i--;
	}
	free(paths);
}

char	**find_command(char **envp)
{
	int		i;
	char	**paths;

	paths = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			break ;
		i++;
	}
	paths = ft_split(envp[i], '=');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*find_path_strjoin(char **paths, int i, char **command)
{
	char	*part_of_path;
	char	*path;

	part_of_path = ft_strjoin(paths[i], "/");
	if (!part_of_path)
		return (NULL);
	path = ft_strjoin(part_of_path, command[0]);
	if (!path)
		return (NULL);
	free(part_of_path);
	return (path);
}

char	**find_path_utils(char **envp, char **command)
{
	int		i;
	char	**paths;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
	}
	if (!envp[i] && check_in_dir(command[0]) == 1)
	{
		paths = find_command(envp);
		return (paths);
	}
	else if (!envp[i] && check_in_dir(command[0]) == 0)
		error_command("command not found: ", command);
	paths = ft_split(envp[i] + 5, ':');
	if (paths == NULL)
		return (NULL);
	return (paths);
}

char	*find_path(char **command, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	paths = find_path_utils(envp, command);
	if (!paths)
		error_command("split failed: ", command);
	while (paths[i])
	{
		path = find_path_strjoin(paths, i, command);
		if (access(path, F_OK) == 0)
		{
			free_paths(paths);
			return (path);
		}
		else
			free(path);
		i++;
	}
	free_paths(paths);
	return (0);
}
