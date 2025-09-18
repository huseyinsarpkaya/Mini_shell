/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merilhan <merilhan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:44:48 by merilhan          #+#    #+#             */
/*   Updated: 2025/08/26 13:52:16 by merilhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <readline/readline.h>

static void	setup_signal_action(int sign, void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(sign, &sa, NULL);
}

static int	ft_event_hook(void)
{
	return (0);
}

static void	ft_init_signals_extra(t_signal_type context_type)
{
	if (context_type == IGNORE)
	{
		setup_signal_action(SIGINT, SIG_IGN);
		setup_signal_action(SIGQUIT, SIG_IGN);
	}
	else if (context_type == DEFAULT)
	{
		setup_signal_action(SIGINT, SIG_DFL);
		setup_signal_action(SIGQUIT, SIG_DFL);
	}
}

void	ft_init_signals(t_signal_type context_type)
{
	g_signal_status = 0;
	if (context_type == PROMPT)
	{
		rl_event_hook = NULL;
		setup_signal_action(SIGINT, ft_prompt_handler);
		setup_signal_action(SIGQUIT, SIG_IGN);
	}
	else if (context_type == EXECUTION)
	{
		rl_event_hook = NULL;
		setup_signal_action(SIGINT, ft_execute_handler);
		setup_signal_action(SIGQUIT, ft_sigquit_handler);
	}
	else if (context_type == HEREDOC)
	{
		rl_event_hook = ft_event_hook;
		setup_signal_action(SIGINT, ft_heredoc_handler);
		setup_signal_action(SIGQUIT, SIG_IGN);
	}
	else
		ft_init_signals_extra(context_type);
}
