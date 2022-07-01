/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 11:55:16 by estarck           #+#    #+#             */
/*   Updated: 2022/07/01 15:13:28 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exit(t_data *shell, t_lst *tmp)
{
	if (tmp->argv[1] != NULL)
	{
		if (tmp->argv[2] != NULL && ft_str_isdigit(tmp->argv[1]->str))
		{
			ft_printf("exit: too many arguments\n");
			shell->code_error = ANY_ERROR;
			tmp = tmp->next;
			return ;
		}
		if (ft_str_isdigit(tmp->argv[1]->str))
			shell->code_error = ft_atoi(tmp->argv[1]->str);
		else
		{
			ft_printf("exit: numerical argument required\n");
			shell->code_error = EXIT_ERROR_ARG;
		}
	}
	else
		shell->code_error = 0;
	free_cmd(shell->cmd);
	if (tmp->next == NULL && tmp->prev == NULL)
		quit_mini(shell);
}
