/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:17:40 by estarck           #+#    #+#             */
/*   Updated: 2022/06/07 09:58:57 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	free_dchar(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
}*/

static void	free_char(char *str)
{
	free(str);
}

static void	free_cmd(t_shell *shell)
{
	t_cmd	*tmp;
	t_cmd	*n_tmp;

	tmp = shell->cmd;
	n_tmp = NULL;
	while (tmp != NULL)
	{
		n_tmp = tmp->next;
		free_char(tmp->argv);
		free(tmp->cmd);
		free(tmp);
		tmp = n_tmp;
	}
	shell->cmd = NULL;
}

void	ft_free(t_shell *shell)
{
	if (shell->cmd != NULL)
		free_cmd(shell);
}
