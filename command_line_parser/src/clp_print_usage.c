/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clp_print_usage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 23:14:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/09/15 23:14:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "clp_data_types.h"
#include "clp_internal.h"

extern t_clp_app	*g_app;

void			clp_print_arg_description(const char *description,
		const char *indent)
{
	char	*new_line;

	new_line = ft_strchr(description, '\n');
	while (new_line)
	{
		ft_putstr(indent);
		write(1, description, new_line - description + 1);
		description = new_line + 1;
		new_line = ft_strchr(description, '\n');
	}
	if (ft_strlen(description))
	{
		ft_putstr(indent);
		ft_putendl(description);
	}
}

t_clp_result	clp_print_param(t_clp_param *param, const char *indent)
{
	char	*arg_indent;

	ft_putstr(indent);
	ft_putstr(param->name);
	ft_putstr(" - ");
	ft_putendl(param->description);
	if (param->argument_description)
	{
		if (!(arg_indent = ft_strjoin(indent, "\t")))
			return (clp_memory_allocation_failure);
		ft_putstr(indent);
		ft_putendl("Arguments:");
		clp_print_arg_description(param->argument_description, arg_indent);
		free(arg_indent);
	}
	return (clp_success);
}

t_clp_result	clp_print_command_usage(t_clp_cmd *cmd)
{
	int				i;
	t_clp_result	r;

	r = clp_print_param(&cmd->param, "\t");
	if (cmd->flag_count || g_app->common_flag_count)
		ft_putendl("\tFlags:");
	i = 0;
	while (i < cmd->flag_count)
		r |= clp_print_param(&cmd->flags[i++].param, "\t\t");
	i = 0;
	while (i < g_app->common_flag_count)
	{
		if (!clp_get_cmd_flag(g_app->common_flags[i].param.name, cmd))
			r |= clp_print_param(&g_app->common_flags[i].param, "\t\t");
		i++;
	}
	return (r);
}

t_clp_result	clp_print_usage(const char *app_name)
{
	int				i;
	t_clp_result	r;

	ft_putstr("\nUsage: ");
	ft_putstr(app_name);
	ft_putendl(" [command] [flags] [parameters]\n");
	ft_putendl("Commands:\n");
	r = clp_success;
	i = 0;
	while (i < g_app->command_count)
	{
		r |= clp_print_command_usage(&g_app->commands[i++]);
		ft_putchar('\n');
	}
	return (r);
}
