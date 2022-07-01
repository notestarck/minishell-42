/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:56:37 by estarck           #+#    #+#             */
/*   Updated: 2022/07/01 14:57:31 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//verifie si le path est valide
int	valid_path(t_data *shell, char *av)
{
	struct stat	buf;

	if (stat(av, &buf) == -1)
	{
		perror("minishell");
		shell->code_error = COMMAND_NOT_FOUND;
		return (COMMAND_NOT_FOUND);
	}
	else
		return (0);
}
