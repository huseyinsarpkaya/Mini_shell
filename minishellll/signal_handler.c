/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merilhan <merilhan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:25:43 by husarpka          #+#    #+#             */
/*   Updated: 2025/08/26 14:12:14 by merilhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <readline/readline.h>

volatile sig_atomic_t	g_signal_status = 0;

void	ft_prompt_handler(int signum)
{
	g_signal_status = signum;
	set_last_exit_status(130);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_sigquit_handler(int signum)
{
	g_signal_status = signum;
	ft_putendl_fd("Quit (core dumped)", 2);
}

void	ft_execute_handler(int signum)
{
	g_signal_status = signum;
	write(STDOUT_FILENO, "\n", 1);
}

void	ft_heredoc_handler(int signum)
{
	g_signal_status = signum;
	rl_done = 1;
	close(STDIN_FILENO);
}
