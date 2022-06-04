/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:17:09 by estarck           #+#    #+#             */
/*   Updated: 2022/06/04 13:59:11 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cpy_args(t_shell *shell, char *str, int l)
{
	int		i;
	int		c_arg;
	int		nb_arg;
	char	*arg;
	t_cmd	*tmp;

	i = 0;
	c_arg = -1;
	arg = malloc(sizeof(char) * l + 1);
	ft_strlcpy(arg, str, l + 1);
	nb_arg = count_argv(shell, arg);
	tmp = add_lst(shell);
	tmp->argv = malloc(sizeof(char *) * nb_arg + 1);
	while (++c_arg < nb_arg)
	{
		while (*arg == ' ' && arg)
			arg++;
		i = argv_length(shell, arg);
 		tmp->argv[c_arg] = malloc(sizeof(char) * i + 1);
 		ft_strlcpy(tmp->argv[c_arg], arg, i + 1);
		arg = arg + i;
		i = 0;
	}
	tmp->argv[c_arg] = NULL;
	free(arg - l);
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
