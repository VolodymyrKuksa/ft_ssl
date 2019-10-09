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

#include "clp.h"
#include "clp_internal.h"

extern t_clp_app	*g_app;

t_clp_result	clp_parse_internal(int argc, char **argv)
{
	t_clp_cmd			*cmd;
	t_clp_flag			*flag;
	t_clp_cmd_arguments	arg;
	int					flags;
	int					i;

	arg.count = argc;
	arg.vector = argv;
	if (argc == 1 || !(cmd = clp_get_cmd(argv[1])))
		return (clp_unknown_command_name);
	flags = 0;
	i = 2;
	while (i < argc)
	{
		if (!(flag = clp_get_cmd_flag(argv[i], cmd)) &&
		!(flag = clp_get_flag(argv[i])))
			break ;
		flag->function(cmd->param.identifier, flags, &arg, i);
		flags |= flag->param.identifier;
		++i;
	}
	return (cmd->function(flags, &arg));
}

t_clp_result	clp_parse(int argc, char **argv)
{
	if (clp_parse_internal(argc, argv) != clp_success)
		return (clp_print_usage(argv[0]));
	return (clp_success);
}
