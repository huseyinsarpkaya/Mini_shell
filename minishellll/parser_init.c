/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merilhan <merilhan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:45:28 by merilhan          #+#    #+#             */
/*   Updated: 2025/08/26 13:51:50 by merilhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_clean_init(t_parser *cmd)
{
	cmd->argv_cap = 1;
	cmd->argv = gb_malloc(sizeof(char *) * cmd->argv_cap);
	cmd->redirs = NULL;
	cmd->next = NULL;
	cmd->heredoc_fd = -2;
}

void	ft_temp_next(t_redirection *new_redir, t_parser *cmd)
{
	t_redirection	*temp;

	temp = cmd->redirs;
	while (temp->next)
		temp = temp->next;
	temp->next = new_redir;
}

void	init_redirection(t_redirection *new_redir, t_redir_type type,
		char *filename, int no_expand)
{
	new_redir->filename = ft_strdup(filename);
	new_redir->type = type;
	new_redir->no_expand = no_expand;
	new_redir->next = NULL;
}

void	finalize_cmd(t_parser *cmd, int argc, t_all *data)
{
	cmd->argv[argc] = NULL;
	if (!(data->cmd_list))
		data->cmd_list = cmd;
	else
		(data->last_cmd)->next = cmd;
	data->last_cmd = cmd;
}
