/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:17:09 by estarck           #+#    #+#             */
/*   Updated: 2022/06/04 09:19:04 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cpy_args(t_shell *shell, char *str, int l)
{
	t_cmd	*tmp;

	tmp = add_lst(shell);
	tmp->argv = malloc(sizeof(char *) * )
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
	if (str[l] == '|')
		l++;
	return (l);
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
	return (1);
}
