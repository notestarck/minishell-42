/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bash_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 05:41:26 by estarck           #+#    #+#             */
/*   Updated: 2022/06/07 08:44:16 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/stat.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	while (src[c] != '\0')
		c++;
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src [i];
			i++;
		}
		dst[i] = '\0';
	}
	return (c);
}

int	check_quote(char *str)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	if (str[i] == '\'')
		s_quote = 1;
	else if (str[i] == '"')
		d_quote = 1;
	while ((s_quote || d_quote) && str[++i] != '\0')
	{
		if (str[i] == '\'' && s_quote == 1)
			s_quote = 0;
		if (str[i] == '"' && d_quote == 1)
			d_quote = 0;
		if (str[i] == '\\')
			i++;
	}
	return (i);
}

int	ft_strchr_i(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		if (str[i] == '"' || str[i] == '\'')
			i = check_quote(&str[i]) + i;
		i++;
	}
	return (i + 1);
}

void	cpy_cmd(char **cmd, char *prompt)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	j = 0;
	while (prompt[i])
	{
		l = 0;
		l = ft_strchr_i(&prompt[i], '|');
		cmd[j] = malloc(sizeof(char) * l + 1);
		ft_strlcpy(cmd[j], &prompt[i], l);
		printf("cpy : %s\n", cmd[j]);
		i += l;
		j++;
	}
	cmd[j] = NULL;
}

char	**init_cmd(char *prompt)
{
	int		i;
	int		j;
	char	**ret;

	i = 1;
	j = 0;
	while (prompt[j])
	{
		if (prompt[j] == '|')
			i++;
		j++;
	}
	ret = malloc(sizeof(char *) * i + 1);
	return (ret);
}

char	*start_shell(void)
{
	char	*ret;

	ret = readline("Mini_Shell -c $ ");
	add_history(ret);
	return (ret);
}

void	run_cmd(char **cmd, char **envp)
{
	int		i;
	char	*bash[4];
	pid_t	pid;
	int		pipefd[2];

	i = 0;
	while (cmd[i] != NULL)
	{
		bash [0] = "/bin/bash";
		bash [1] = "-c";
		bash [2] = cmd[i];
		bash [3] = NULL;
		if (pipe(pipefd) == -1)
			perror ("error : pipe");
		pid = fork();
		if (pid == -1)
			perror ("error : fork");
		if (pid == 0)
		{
			close (pipefd[0]);
			if (cmd[i + 1] != NULL)
				dup2 (pipefd[1], STDOUT_FILENO);
			execve("/bin/bash", bash, envp);
			perror("error : execve");
		}
		else
		{
			close (pipefd[1]);
			dup2 (pipefd[0], STDIN_FILENO);
			waitpid(-1, NULL, 0);
			i++;
			printf("i : %d\n", i);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	**cmd;

	while (42)
	{
		prompt = start_shell();
		cmd = init_cmd(prompt);
		cpy_cmd(cmd, prompt);
		run_cmd(cmd, envp);
		free (cmd); //avec chaque ligne a rajouter
	}
	return (0);
}