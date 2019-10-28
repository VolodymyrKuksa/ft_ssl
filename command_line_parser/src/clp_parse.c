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

t_clp_result	clp_parse_internal(t_clp_cmd_arguments arg)
{
	t_clp_cmd			*cmd;
	t_clp_flag			*flag;
	int					flags;
	int					i;
	t_clp_result		r;

	if (arg.count == 1 || !(cmd = clp_get_cmd(arg.vector[1])))
		return (clp_unknown_command_name);
	flags = 0;
	i = 2;
	while (i < arg.count)
	{
		if (!(flag = clp_get_cmd_flag(arg.vector[i], cmd)) &&
		!(flag = clp_get_flag(arg.vector[i])))
			break ;
		if (flag->function)
		{
			r = flag->function(cmd->param.identifier, flags, &arg, &i);
			if (r != clp_success)
				return (r);
		}
		flags |= flag->param.identifier;
		++i;
	}
	return (cmd->function(cmd->param.identifier, flags, &arg, i));
}

t_clp_result	clp_parse(int argc, char **argv)
{
	t_clp_cmd_arguments		arg;
	t_clp_result			r;

	arg.count = argc;
	arg.vector = argv;
	r = clp_parse_internal(arg);
	if (r != clp_success)
		return (clp_print_usage(argv[0]));
	return (clp_success);
}
