/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:17:09 by estarck           #+#    #+#             */
/*   Updated: 2022/06/07 16:14:52 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cpy_args(t_shell *shell, char *str, int l)
{
	t_cmd	*tmp;

	tmp = add_lst(shell);
	tmp->argv = malloc(sizeof(char) * l + 1);
	ft_strlcpy(tmp->argv, str, l);
}

static int	count_pip(t_shell *shell, char *str)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
			i = check_quote(shell, &str[i]) + i;
		if (str[i] == '|' && str[i + 1] != '|')
			p++;
		else if (str[i] == '|' && str[i + 1] == '|')
			i++;
		i++;
	}
	return (p);
}

static int	find_pip(t_shell *shell, char *str)
{
	int	l;

	l = 0;
	while (str[l] != '|' && str[l] != '\0')
	{
		if (str[l] == '\'' || str[l] == '"')
			l = check_quote(shell, &str[l]) + l;
		l++;
	}
	return (l + 1);
}

int	parsing(t_shell *shell)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (shell->ret_prompt[i] != '\0')
	{
		l = find_pip(shell, &shell->ret_prompt[i]);
		if (check_error(shell))
			return (0);
		cpy_args(shell, &shell->ret_prompt[i], l);
		i = l + i;
	}
	shell->nbr_pipe = count_pip(shell, shell->ret_prompt);
	return (1);
}
