/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:19:55 by ntenisha          #+#    #+#             */
/*   Updated: 2022/03/27 18:19:57 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	str1;
	size_t	str2;
	size_t	i;
	char	*memory;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	str1 = ft_strlen(s1);
	str2 = ft_strlen(s2);
	memory = (char *)malloc(sizeof(*memory) * (str1 + str2 + 1));
	if (!memory)
		return (NULL);
	while (*s1 != '\0')
		memory[i++] = *s1++;
	while (*s2 != '\0')
		memory[i++] = *s2++;
	memory[i] = '\0';
	return (memory);
}
