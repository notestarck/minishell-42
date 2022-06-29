/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:52:00 by estarck           #+#    #+#             */
/*   Updated: 2022/06/29 19:52:08 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_arg(t_lst *cmd, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '|' && str[i])
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '|' || str[i] == 32 || (str[i] >= 9 && str[i] <= 13) || str[i] == '\'' || str[i] == '"')
		{
			if (str[i] == '\'' || str[i] == '"')
				i = check_quote(cmd, &str[i]) + i + 1;
			else if ((str[i] == '>' || str[i] == '<') && str[i + 1] != '>' && str[i + 1] != '<' && str[i - 1] != '\\' && str[i])
				i++;
			else if ((str[i] == '>' || str[i] == '<') && (str[i + 1] == '>' || str[i + 1] == '<') && str[i - 1] != '\\' && str[i])
				i += 2;
			break ;
		}
		else if (str[i] != '<' && str[i] != '>' && str[i] != '|' && str[i])
		{
			while (str[i] != '<' && str[i] != '>' && str[i] != '|' && str[i] != 32 && !(str[i] >= 9 && str[i] <= 13) && str[i])
			{
				if (str[i] == '\'' || str[i] == '"')
					i = check_quote(cmd, &str[i]) + i + 1;
				if (str[i] == '\\')
					i += 2;
				else
					i++;
			}
			break ;
		}
	printf("i = %d\n", i);
	}
	return (i);
}

static int	cpy_arg(t_lst *cmd, char *str)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	j = 0;
	while (str[i] && (str[i] != '|' || str[i + 1] == '|'))
	{
		l = 0;
		l = parse_arg(cmd, &str[i]);
		cmd->argv[j] = malloc(sizeof(char) * (l + 1));
		if (!cmd->argv[j])
			perror("error : malloc");
		ft_strlcpy(cmd->argv[j], &str[i], l + 1);
		i = i + l;
		while (str[i] == ' ' && str[i] != '\0')
			i++;
		j++;
	}
	cmd->argv[j] = NULL;
	if (str[i] == '|')
		i++;
	return (i);
}

static void	init_arg(t_lst *cmd, char *str)
{
	cmd->argv = malloc(sizeof(char *) * (count_argv(cmd, str) + 1));
	if (!cmd->argv)
		perror("error : malloc");
}

static void	split(t_data *shell, t_lst *cmd)
{
	t_lst	*tmp;
	char	*str;

	tmp = cmd;
	str = ft_strcut(shell->ret_prompt, ' ');
	if (*str == '\0')
		cmd->error = 1;
	while (*str != '\0')
	{
		init_arg(tmp, str);
		str = cpy_arg(tmp, str) + str;
		if (*str != '\0')
		{
			shell->nbr_cmd = shell->nbr_cmd + 1;
			tmp = add_cmd(cmd);
			str = ft_strcut(str, ' ');
		}
	}
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

int	pre_process(t_data *shell, t_lst *cmd)
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
			continue;
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

t_lst	*parse_prompt(t_data *shell)
{
	t_lst		*cmd;

	cmd = new_cmd();
	if (!pre_process(shell, cmd))
		cmd->error = 1;

	/*
	Apres la fonction preprocess, tout les arguments sont rangés dans une liste chainée:
				typedef enum e_type
				{
					NONE = -1,
					ARG,
					S_RIGHT,
					S_LEFT,
					D_RIGHT,
					D_LEFT,
					PIPE,
					AND,
					OR,
					WLCRD
				}	t_type;

				typedef struct s_arg
				{
					t_type	type;
					char	*str;
				}	t_arg;
	Le type permet de différencier entre un \| et un |   et   >> et \>\> ou \>> :
	si l'utilisateur échappe un charactère il sera compté comme un argument (il aura un t_type de 0)

	Une fois la commande exectué, la liste est dans shell->cmd_list
	Peut tu refaires un petit parseur de shell->cmd_list qui créé des nouvelles 't_lst *cmd' ?
	Les variables ne marcheront surement qu'a moitié mais je m'en occuperais jeudi
	Je vais me coucher tot pour pas etre trop décalé avec toi, donc normalement on se verra tot

	PS: la fonction pre_process fait 175 lignes, je vais bien m'amuser demain
	*/

	//Je met error a un juste pour ne pas
	//executer les commandes pendant que je teste
	//Tu peux enlever
	cmd->error = 1;
	//split(shell, cmd);
	return (cmd);
}
