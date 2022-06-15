/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 23:27:06 by reclaire          #+#    #+#             */
/*   Updated: 2022/06/14 23:27:06 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get(t_data *shell, char *key)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], key, ft_strlen(key)))
			return (ft_substr(shell->env[i], ft_strlen(key) + 1,
					ft_strlen(shell->env[i])));
		i++;
	}
	return (NULL);
}

void	env_new(t_data *shell, char *key, char *value)
{
	int		size;
	int		i;
	char	**out;

	size = 0;
	while (shell->env[size])
		size++;
	size += 2;
	out = malloc(sizeof(char *) * size);
	i = 0;
	while (i < size - 1)
	{
		out[i] = shell->env[i];
		i++;
	}
	out[i] = value;
	out[i + 1] = NULL;
}

/* Set a env variable, identified by "key" to "value". 
"value" needs to be on the heap.*/
void	env_set(t_data *shell, char *key, char *value)
{
	int		i;
	char	*tmp;

	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], key, ft_strlen(key)))
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(key);
			tmp = ft_strjoin(shell->env[i], "=");
			free(shell->env[i]);
			shell->env[i] = ft_strjoin(tmp, value);
			free(tmp);
			return ;
		}
		i++;
	}
	env_new(shell, key, value);
}
