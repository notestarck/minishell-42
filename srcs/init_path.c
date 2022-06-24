/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:15:33 by estarck           #+#    #+#             */
/*   Updated: 2022/06/24 15:15:25 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//recherche les != PATH dans l'env
void	init_env_path(t_data *shell)
{
	char	*envp;

	envp = env_get(shell, "PATH");
	if (!*envp)
		shell->env_path = ft_split(ft_strdup("\0"), ':');
	else
		shell->env_path = ft_split(ft_strchr(envp, '/'), ':');
}
