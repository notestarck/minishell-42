/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:30:23 by estarck           #+#    #+#             */
/*   Updated: 2022/06/30 21:51:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error(t_data *shell, t_lst *cmd)
{
	t_lst	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->er_quote == 1 || tmp->error == 1)
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
		tmp = tmp->next;
	}
	return (0);
}
