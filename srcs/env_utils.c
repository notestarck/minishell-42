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

void	env_del(t_data *shell, char *key)
{
	int		size;
	int		i;
	int		j;
	char	**out;
	char	*curr;

	size = 0;
	while (shell->env[size])
		size++;
	out = malloc(sizeof(char *) * size);
	i = 0;
	j = 0;
	while (i < size)
	{
		curr = ft_substr(shell->env[i + j], 0, ft_strlen(key));
		if (!ft_strncmp(curr, key, ft_strlen(key) + 1))
		{
			free(shell->env[i + j]);
			j++;
			break ;
		}
		out[i] = ft_strdup(shell->env[i + j]);
		free(shell->env[i + j]);
		i++;
	}
	out[i] = NULL;
	free(shell->env);
	shell->env = out;
}

void	env_new(t_data *shell, char *key, char *value)
{
	int		size;
	int		i;
	char	**out;
	char	*tmp;

	size = 0;
	while (shell->env[size])
		size++;
	size += 2;
	out = malloc(sizeof(char *) * size);
	i = 0;
	while (i < size - 2)
	{
		out[i] = shell->env[i];
		i++;
	}
	tmp = ft_strjoin(key, "=");
	out[i] = ft_strjoin(tmp, value);
	free(tmp);
	out[i + 1] = NULL;
	free(shell->env);
	shell->env = out;
}

/* Set a env variable, identified by "key" to "value". 
"value" needs to be on the heap.*/
void	env_set(t_data *shell, char *key, char *value)
{
	int		i;
	char	*tmp;
	char	*curr;

	i = 0;
	while (shell->env[i])
	{
		curr = ft_substr(shell->env[i], 0, ft_strlen(key));
		if (!ft_strncmp(curr, key, ft_strlen(key) + 1))
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(key);
			tmp = ft_strjoin(shell->env[i], "=");
			free(shell->env[i]);
			shell->env[i] = ft_strjoin(tmp, value);
			free(tmp);
			return ;
		}
		free(curr);
		i++;
	}
	env_new(shell, key, value);
}
