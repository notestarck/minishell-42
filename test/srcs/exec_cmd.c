/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 09:11:42 by estarck           #+#    #+#             */
/*   Updated: 2022/06/07 16:16:58 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_pipe(t_shell *shell)
{
    int		status;
    int		i;
    pid_t 	pid;
    int		pipefds[2 * shell->nbr_pipe];
	t_cmd	*cmd;

	cmd = shell->cmd;
	i = 0;
    for(i = 0; i < (shell->nbr_pipe); i++){
        if(pipe(pipefds + i * 2) < 0) {
            perror("couldn't pipe");
            exit(EXIT_FAILURE);
        }
    }
    int j = 0;
    while(cmd) {
        pid = fork();
		if(pid < 0){
            perror("error");
            exit(EXIT_FAILURE);
        }
        if(pid == 0) {
            if(cmd->next){
                if(dup2(pipefds[j + 1], STDOUT_FILENO) < 0){
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }
            if(j != 0 ){
                if(dup2(pipefds[j-2], STDIN_FILENO) < 0){
                    perror(" dup2");///j-2 0 j+1 1
                    exit(EXIT_FAILURE);
                }
            }
            for(i = 0; i < 2*shell->nbr_pipe; i++){
                    close(pipefds[i]);
            }
            if( execve(*cmd->cmd, cmd->cmd, shell->env) < 0 ){
                    perror(*cmd->cmd);
                    exit(EXIT_FAILURE);
            }
        }
        cmd = cmd->next;
        j+=2;
    }
    for(i = 0; i < 2 * shell->nbr_pipe; i++){
        close(pipefds[i]);
    }
    for(i = 0; i < shell->nbr_pipe + 1; i++)
        wait(&status);
}

void	exec_all(t_shell *shell)
{
	run_pipe(shell);
}
