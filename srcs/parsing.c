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
			cmd->argv[i] = tmp->content;
			if (ft_isrange((int)(cmd->argv[i]->type), 0, 3))
			{
				if (cmd->sep != -1 && cmd->sep != D_LEFT)
				{
					perror("Double redirection");
					shell->code_error = SYNTAX_ERROR;
					return ;
				}
				cmd->sep = cmd->argv[i]->type;
			}
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
			if (((t_arg *)tmp->content)->type == PIPE)
				i--;
			cmd->argv = malloc(sizeof(t_arg *) * (i + 1));
			i = 1;
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

	//t_lst *cmd = shell->cmd;
	//while (cmd)
	//{
	//	int i = 0;
	//	while (cmd->argv[i])
	//	{
	//		ft_printf("			%s %d\n", cmd->argv[i]->str, cmd->argv[i]->type);
	//		i++;
	//	}
	//	ft_printf("\n");
	//	cmd = cmd->next;
	//}

}

void	append_char(char **str, char c)
{
	char	*cpy;

	cpy = ft_malloc(sizeof(char) * 2);
	cpy[0] = c;
	cpy[1] = '\0';
	*str = ft_str_appnd(*str, cpy, 1, 1);
}

void	push(t_list **args, char **str, t_type type, t_list **s_quotes, t_list **d_quotes)
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
	arg->d_quotes = *d_quotes;
	arg->s_quotes = *s_quotes;
	*s_quotes = NULL;
	*d_quotes = NULL;
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
	t_list	*lst_s_quotes;
	t_list	*lst_d_quotes;
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
				int *n = ft_malloc(sizeof(int));
				*n = ft_strlen(new) - 1;
				ft_lstadd_back(&lst_s_quotes, ft_lstnew(n));
				i++;
				continue ;
			}
			append_char(&new, str[i]);
			i++;
			continue ;
		}
		if (d_quote)
		{
			if (str[i] == '\"' && !d_quote_escape)
			{
				int *n = ft_malloc(sizeof(int));
				*n = ft_strlen(new) - 1;
				ft_lstadd_back(&lst_d_quotes, ft_lstnew(n));
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
			int *n = ft_malloc(sizeof(int));
			*n = ft_strlen(new);
			ft_lstadd_back(&lst_s_quotes, ft_lstnew(n));
			s_quote = 1;
			i++;
			continue ;
		}
		if (str[i] == '\"' && !escape)
		{
			int *n = ft_malloc(sizeof(int));
			*n = ft_strlen(new);
			ft_lstadd_back(&lst_d_quotes, ft_lstnew(n));
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
			push(&args, &new, ARG, &lst_s_quotes, &lst_d_quotes);
			new = ft_strdup("|");
			push(&args, &new, PIPE, &lst_s_quotes, &lst_d_quotes);
			new = ft_strdup("");
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
			push(&args, &new, ARG, &lst_s_quotes, &lst_d_quotes);
			new = ft_strdup("");
			append_char(&new, '>');
			append_char(&new, '>');
			push(&args, &new, D_RIGHT, &lst_s_quotes, &lst_d_quotes);
			new = ft_malloc(sizeof(char));
			*new = '\0';
			i += 2;
			continue ;
		}
		if (!ft_strncmp(str + i, "<<", 2))
		{	
			push(&args, &new, ARG, &lst_s_quotes, &lst_d_quotes);
			new = ft_malloc(sizeof(char));
			*new = '\0';
			append_char(&new, '<');
			append_char(&new, '<');
			push(&args, &new, D_LEFT, &lst_s_quotes, &lst_d_quotes);
			new = ft_malloc(sizeof(char));
			*new = '\0';
			i += 2;
			continue ;
		}
		if (!ft_strncmp(str + i, ">", 1))
		{	
			push(&args, &new, ARG, &lst_s_quotes, &lst_d_quotes);
			new = ft_malloc(sizeof(char));
			*new = '\0';
			append_char(&new, '>');
			push(&args, &new, S_RIGHT, &lst_s_quotes, &lst_d_quotes);
			new = ft_malloc(sizeof(char));
			*new = '\0';
			i++;
			continue ;
		}
		if (!ft_strncmp(str + i, "<", 1))
		{	
			push(&args, &new, ARG, &lst_s_quotes, &lst_d_quotes);
			new = ft_malloc(sizeof(char));
			*new = '\0';
			append_char(&new, '<');
			push(&args, &new, S_LEFT, &lst_s_quotes, &lst_d_quotes);
			new = ft_malloc(sizeof(char));
			*new = '\0';
			i++;
			continue ;
		}
		if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13) && !escape)
		{
			push(&args, &new, ARG, &lst_s_quotes, &lst_d_quotes);
			new = ft_malloc(sizeof(char));
			*new = '\0';
			i++;
			continue ;
		}
		if (escape)
		{
			int *n = ft_malloc(sizeof(int));
			*n = ft_strlen(new);
			ft_lstadd_back(&lst_s_quotes, ft_lstnew(n));
			n = ft_malloc(sizeof(int));
			*n = ft_strlen(new);
			ft_lstadd_back(&lst_s_quotes, ft_lstnew(n));
		}
		escape = 0;
		append_char(&new, str[i]);
		i++;
	}
	push(&args, &new, ARG, &lst_s_quotes, &lst_d_quotes);
	ft_lstremoveif(&args, &free_arg, &cmp, NULL);
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
}
