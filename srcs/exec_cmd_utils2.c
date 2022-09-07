/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:43:39 by estarck           #+#    #+#             */
/*   Updated: 2022/09/07 17:03:19 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_var4(t_arg *arg, int i, int start, char *value)
{
	char	*out;

	out = ft_substr(arg->str, 0, start);
	out = ft_str_appnd(out, value, 1, 1);
	out = ft_str_appnd(out, arg->str + start + i, 1, 0);
	free(arg->str);
	arg->str = out;
}

void	insert_var3(t_arg *arg, char *key, int j)
{
	t_list	*lst1;
	t_list	*lst2;

	lst1 = arg->s_quotes;
	lst2 = arg->d_quotes;
	while (lst2)
	{
		if (*((int *)lst2->content) >= 0
			&& *((int *)lst2->content) <= (int)ft_strlen(key) - 1)
		{
			lst1 = lst2->next;
			ft_lstremove(&arg->s_quotes, lst2, NULL);
			lst2 = lst1;
		}
		else
		{
			*((int *)lst2->content) += j - ft_strlen(key) - 1;
			lst2 = lst2->next;
		}
	}
}

void	insert_var2(t_arg *arg, char *key, int j)
{
	t_list	*lst1;
	t_list	*lst2;

	lst1 = arg->s_quotes;
	lst2 = arg->d_quotes;
	while (lst1)
	{
		if (*((int *)lst1->content) >= 0
			&& *((int *)lst1->content) <= (int)ft_strlen(key) - 1)
		{
			lst2 = lst1->next;
			ft_lstremove(&arg->s_quotes, lst1, NULL);
			lst1 = lst2;
		}
		else
		{
			*((int *)lst1->content) += j - ft_strlen(key) - 1;
			lst1 = lst1->next;
		}
	}
}

int	insert_var(t_data *shell, t_arg *arg, int start)
{
	char	*key;
	char	*value;
	int		i;
	int		j;

	i = 1;
	if (arg->str[start + i] == '?')
		return (insert_var_inter(shell, &arg->str, start), 1);
	j = is_in_quotes(start, arg);
	while (arg->str[start + i] && ft_isalnum(arg->str[start + i])
		&& j == is_in_quotes(start + i, arg))
		i++;
	key = malloc(sizeof(char) * i);
	ft_strlcpy(key, arg->str + start + 1, i);
	value = env_get(shell, key);
	j = ft_strlen(value);
	insert_var2(arg, key, j);
	insert_var3(arg, key, j);
	insert_var4(arg, i, start, value);
	free(key);
	if (i == 0)
		return (j);
	else
		return (j - 1);
}
