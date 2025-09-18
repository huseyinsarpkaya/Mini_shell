/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merilhan <merilhan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:45:43 by merilhan          #+#    #+#             */
/*   Updated: 2025/08/26 13:51:52 by merilhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token	*ft_control_token(t_token *tokens, t_all *data)
{
	int			argc;
	t_parser	*cmd;

	argc = 0;
	cmd = gb_malloc(sizeof(t_parser));
	ft_clean_init(cmd);
	while (tokens && tokens->type != TOKEN_PIPE && tokens->type != TOKEN_EOF)
		ft_loop(&tokens, cmd, &argc, data);
	finalize_cmd(cmd, argc, data);
	if (tokens && tokens->type == TOKEN_PIPE)
		tokens = tokens->next;
	return (tokens);
}

t_all	*ft_all_init(t_all *all, t_env *env)
{
	all->cmd_list = NULL;
	all->last_cmd = NULL;
	all->env_list = env;
	return (all);
}

t_parser	*parse_tokens(t_token *tokens, t_env *env_list)
{
	t_all		*all;
	t_parser	*cmd;

	cmd = gb_malloc(sizeof(t_parser));
	all = gb_malloc(sizeof(t_all));
	all = ft_all_init(all, env_list);
	if (ft_syn(tokens))
		return (NULL);
	while (tokens && tokens->type != TOKEN_EOF)
		tokens = ft_control_token(tokens, all);
	cmd = all->cmd_list;
	return (cmd);
}
