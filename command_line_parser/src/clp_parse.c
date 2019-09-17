/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clp_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 22:54:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/09/15 22:54:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "clp.h"
#include "clp_internal.h"

extern t_clp_app	*g_app;

t_clp_cmd		*clp_get_cmd(const char *name)
{
	int i;

	i = 0;
	while (i < g_app->command_count)
	{
		if (!ft_strcmp(name, g_app->commands[i].param.name))
			return (&g_app->commands[i]);
		i++;
	}
	return (NULL);
}

t_clp_flag		*clp_get_cmd_flag(const char *name, t_clp_cmd *cmd)
{
	int i;

	i = 0;
	while (i < cmd->flag_count)
	{
		if (!ft_strcmp(name, cmd->flags[i].param.name))
			return (&cmd->flags[i]);
		i++;
	}
	return (NULL);
}

t_clp_flag		*clp_get_flag(const char *name)
{
	int i;

	i = 0;
	while (i < g_app->common_flag_count)
	{
		if (!ft_strcmp(name, g_app->common_flags[i].param.name))
			return (&g_app->common_flags[i]);
		i++;
	}
	return (NULL);
}

t_clp_result	clp_parse_internal(int argc, char **argv)
{
	t_clp_cmd	*cmd;
	t_clp_flag	*flag;
	int			flags;
	int			i;

	if (argc == 1 || !(cmd = clp_get_cmd(argv[1])))
		return (clp_unknown_command_name);
	flags = 0;
	i = 2;
	while (i < argc)
	{
		if (!(flag = clp_get_cmd_flag(argv[i], cmd)) &&
		!(flag = clp_get_flag(argv[i])))
			break ;
		flags |= flag->value;
		++i;
	}
	return (cmd->function(flags, argc - i, argv + i));
}

t_clp_result	clp_parse(int argc, char **argv)
{
	if (clp_parse_internal(argc, argv) != clp_success)
		return (clp_print_usage(argv[0]));
	return (clp_success);
}
