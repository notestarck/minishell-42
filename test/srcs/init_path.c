/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:15:33 by estarck           #+#    #+#             */
/*   Updated: 2022/06/09 11:29:29 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//recherche les != PATH dans l'env
void	init_env_path(t_data *shell)
{
	char	*envp;

	envp = getenv("PATH");
	shell->env_path = ft_split(ft_strchr(envp, '/'), ':');
}
