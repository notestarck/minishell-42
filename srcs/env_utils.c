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

void	init_env(t_data *shell, char **env)
{
	int	i;

	i = 0;
	(void)shell;
	while (env[i])
		i++;
	shell->env = malloc(sizeof(char *) * (i + 1));
	if (shell->env == NULL)
		perror("error : malloc env");
	i = 0;
	while (env[i])
	{
		shell->env[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		ft_strlcpy(shell->env[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	shell->env[i] = NULL;
}

char	*env_get(t_data *shell, char *key)
{
	int		i;
	char	*out;

	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], key, ft_strlen(key)))
			return (ft_substr(shell->env[i], ft_strlen(key) + 1,
					ft_strlen(shell->env[i])));
		i++;
	}
	out = malloc(sizeof(char));
	if (out == NULL)
		return (perror("error : malloc"), NULL);
	out[0] = '\0';
	return (out);
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
	while (i < size && j < size)
	{
		curr = ft_substr(shell->env[j], 0, ft_strchr(shell->env[j], '=') - (shell->env[i]));
		if (!ft_strncmp(curr, key, ft_strlen(curr)))
			free(shell->env[j++]);
		else
		{
			out[i++] = ft_strdup(shell->env[j]);
			free(shell->env[j++]);
		}
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
			free(curr);
			return ;
		}
		free(curr);
		i++;
	}
	env_new(shell, key, value);
}
