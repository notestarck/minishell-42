/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:52:00 by estarck           #+#    #+#             */
/*   Updated: 2022/06/30 11:07:54by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cpy_cmd(t_data *shell)
{
	int		i;
	t_list	*tmp;
	t_lst	*cmd;

	i = 0;
	tmp = shell->cmd_list;
	cmd = shell->cmd;
	while (tmp)
	{
		while (tmp && ((t_arg *)tmp->content)->type != PIPE)
		{
			cmd->argv[i] = ft_strdup(((t_arg *)tmp->content)->str);
			cmd->sep = ((t_arg *)tmp->content)->type;
			i++;
			tmp = tmp->next;
		}
		cmd->argv[i] = NULL;
		i = 0;
		if (tmp)
		{
			cmd = cmd->next;
			tmp = tmp->next;
		}
	}
}

static void	init_cmd(t_data *shell)
{
	int		i;
	t_list	*tmp;
	t_lst	*cmd;

	i = 1;
	tmp = shell->cmd_list;
	shell->cmd = new_cmd();
	cmd = shell->cmd;
	while (tmp)
	{
		if (((t_arg *)tmp->content)->type == PIPE || tmp->next == NULL)
		{
			cmd->argv = malloc(sizeof(char *) * (i + 1));
			i = 0;
			tmp = tmp->next;
			if (tmp)
				cmd = add_cmd(shell->cmd);
			continue ;
		}
		i++;
		tmp = tmp->next;
	}
}

static void	split(t_data *shell)
{
	init_cmd(shell);
	cpy_cmd(shell);

}

void	append_char(char **str, char c)
{
	char	*cpy;

	cpy = ft_malloc(sizeof(char) * 2);
	cpy[0] = c;
	cpy[1] = '\0';
	*str = ft_str_appnd(*str, cpy, 1, 1);
}

void	push(t_list **args, char **str, t_type type)
{
	int		start;
	int		end;
	int		i;
	t_arg	*arg;

	if (*str == NULL)
		return ;
	arg = ft_malloc(sizeof(t_arg));
	start = 0;
	while ((*str)[start] == 32 || ((*str)[start] >= 9 && (*str)[start] <= 13))
		start++;
	end = ft_strlen((*str));
	while ((*str)[end] == 32 || ((*str)[end] >= 9 && (*str)[end] <= 13))
		end--;
	arg->str = ft_malloc(sizeof(char) * (end - start));
	i = 0;
	while (i + start < end)
	{
		arg->str[i] = (*str)[i + start];
		i++;
	}
	arg->str[i] = '\0';
	free(*str);
	*str = NULL;
	arg->type = type;
	ft_lstadd_back(args, ft_lstnew(arg));
}

void	free_arg(void *t)
{
	t_arg	*a;

	a = (t_arg *)t;
	free(a->str);
	free(a);
}

int cmp(t_arg *data, void *ref)
{
	int	i;

	(void)ref;
	if (data->str[0] == '\0')
		return (1);
	i = 0;
	while (data->str[i] == 32 || (data->str[i] >= 9 && data->str[i] <= 13))
		i++;
	return (i == ft_strlen(data->str));
}

int	pre_process(t_data *shell)
{
	int		i;
	int		escape;
	int		s_quote;
	int		d_quote;
	int		d_quote_escape;
	int		size;
	char	*str;
	char	*new;
	t_list	*args;

	i = 0;
	size = 0;
	escape = 0;
	d_quote_escape = 0;
	s_quote = 0;
	d_quote = 0;
	str = shell->ret_prompt;
	new = ft_malloc(sizeof(char));
	*new = '\0';
	i = 0;
	args = NULL;
	while (str[i])
	{
		if (s_quote)
		{
			if (str[i] == '\'')
			{
				s_quote = 0;
				i++;
				continue ;
			}
			printf("c = %c", str[i]);
			append_char(&new, str[i]);
			i++;
			continue ;
		}
		if (d_quote)
		{
			if (str[i] == '\"' && !d_quote_escape)
			{
				d_quote = 0;
				i++;
				continue ;
			}
			else if (str[i] == '\\' && d_quote_escape)
			{
				d_quote_escape = 0;
				append_char(&new, str[i]);
				i++;
				continue ;
			}
			else if (str[i] == '\\' && !d_quote_escape)
			{
				d_quote_escape = 1;
				i++;
				continue ;
			}
			d_quote_escape = 0;
			append_char(&new, str[i]);
			i++;
			continue ;
		}
		if (str[i] == '\'' && !escape)
		{
			s_quote = 1;
			i++;
			continue ;
		}
		if (str[i] == '\"' && !escape)
		{
			d_quote = 1;
			i++;
			continue ;
		}
		if (str[i] == '\\' && !escape)
		{
			escape = 1;
			i++;
			continue ;
		}
		if (str[i] == '|' && !escape)
		{
			push(&args, &new, ARG);
			new = ft_strdup("|");
			push(&args, &new, PIPE);
			i++;
			continue ;
		}
		if (ft_strchr("><|", str[i]) && escape)
		{
			escape = 0;
			append_char(&new, str[i]);
			i++;
			continue ;
		}
		if (!ft_strncmp(str + i, ">>", 2))
		{
			push(&args, &new, ARG);
			new = ft_malloc(sizeof(char));
			*new = '\0';
			append_char(&new, '>');
			append_char(&new, '>');
			push(&args, &new, D_RIGHT);
			new = ft_malloc(sizeof(char));
			*new = '\0';
			i += 2;
			continue ;
		}
		if (!ft_strncmp(str + i, "<<", 2))
		{	
			push(&args, &new, ARG);
			new = ft_malloc(sizeof(char));
			*new = '\0';
			append_char(&new, '<');
			append_char(&new, '<');
			push(&args, &new, D_LEFT);
			new = ft_malloc(sizeof(char));
			*new = '\0';
			i += 2;
			continue ;
		}
		if (!ft_strncmp(str + i, ">", 1))
		{	
			push(&args, &new, ARG);
			new = ft_malloc(sizeof(char));
			*new = '\0';
			append_char(&new, '>');
			push(&args, &new, S_RIGHT);
			new = ft_malloc(sizeof(char));
			*new = '\0';
			i++;
			continue ;
		}
		if (!ft_strncmp(str + i, "<", 1))
		{	
			push(&args, &new, ARG);
			new = ft_malloc(sizeof(char));
			*new = '\0';
			append_char(&new, '<');
			push(&args, &new, S_LEFT);
			new = ft_malloc(sizeof(char));
			*new = '\0';
			i++;
			continue ;
		}
		if (str[i] == ' ' && !escape)
		{
			push(&args, &new, ARG);
			new = ft_malloc(sizeof(char));
			*new = '\0';
			i++;
			continue ;
		}
		escape = 0;
		append_char(&new, str[i]);
		i++;
	}
	push(&args, &new, ARG);
	ft_lstremoveif(&args, &free_arg, &cmp, NULL);

	//Print l'entiereté des arguments, avec leurs types
	t_list *cpy = args;
	while (cpy)
	{
		ft_printf("|>%s<| %d\n", ((t_arg *)cpy->content)->str, ((t_arg *)cpy->content)->type);
		cpy = cpy->next;
	}
	//Fin du print

	shell->cmd_list = args;

	if (s_quote || d_quote)
		return (0);
	return (1);
}

void	parse_prompt(t_data *shell)
{
	if (!pre_process(shell))
		exit(0);
	split(shell);

	//shell->cmd->error = 0;
}
