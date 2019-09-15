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

# include "libft.h"
# include "clp_data_types.h"
# include "clp_internal.h"

extern t_clp_app	*app;

void	clp_print_param(t_clp_param *param, const char *indent)
{
	ft_putstr(indent);
	ft_putstr(param->name);
	ft_putstr(" - ");
	ft_putendl(param->description);
}

void	clp_print_command_usage(t_clp_cmd *cmd)
{
	int		i;

	clp_print_param(&cmd->param, "\t");
	if (cmd->flag_count || app->common_flag_count)
		ft_putendl("\tFlags:");
	i = 0;
	while (i < cmd->flag_count)
		clp_print_param(&cmd->flags[i++].param, "\t\t");
	i = 0;
	while (i < app->common_flag_count) {
		if (!clp_get_cmd_flag(app->common_flags[i].param.name, cmd))
			clp_print_param(&app->common_flags[i].param, "\t\t");
		i++;
	}
}

void	clp_print_usage(const char *app_name)
{
	int i;

	ft_putstr("\nUsage: ");
	ft_putstr(app_name);
	ft_putendl(" [command] [flags] [parameters]\n");
	ft_putendl("Commands:\n");
	i = 0;
	while (i < app->command_count)
	{
		clp_print_command_usage(&app->commands[i++]);
		ft_putchar('\n');
	}
}
