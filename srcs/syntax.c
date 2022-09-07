/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:17:11 by estarck           #+#    #+#             */
/*   Updated: 2022/09/07 17:17:14 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_tmp_error(t_data *shell, t_lst *tmp)
{
	if ((tmp->er_quote == 1 || tmp->error == 1)
		|| (tmp->heredoc && tmp->sep == S_RIGHT)
		|| (tmp->heredoc && tmp->sep == D_RIGHT))
	{
		ft_printf("-minishell: Syntax error\n");
		shell->code_error = SYNTAX_ERROR;
		return (1);
	}
	if (tmp->argv == NULL)
		return (1);
	if (tmp->argv[0] == NULL)
	{
		shell->code_error = SYNTAX_ERROR;
		ft_printf("-minishell: Syntax error\n");
		return (1);
	}
	return (0);
}

int	check_error(t_data *shell, t_lst *cmd)
{
	t_lst	*tmp;

	tmp = cmd;
	if (shell->code_error == -42)
	{
		shell->code_error = SYNTAX_ERROR;
		return (1);
	}
	while (tmp)
	{
		if (check_tmp_error(shell, tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
