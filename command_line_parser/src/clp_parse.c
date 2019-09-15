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

# include "libft.h"
# include "clp.h"
# include "clp_internal.h"

extern t_clp_app	*app;

t_clp_cmd		*clp_get_cmd(const char* name)
{
	int i;

	i = 0;
	while (i < app->command_count)
	{
		if (!ft_strcmp(name, app->commands[i].param.name))
			return (&app->commands[i]);
		i++;
	}
	return (NULL);
}

t_clp_flag		*clp_get_cmd_flag(const char* name, t_clp_cmd *cmd)
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

t_clp_flag		*clp_get_flag(const char* name)
{
	int i;

	i = 0;
	while (i < app->common_flag_count)
	{
		if (!ft_strcmp(name, app->common_flags[i].param.name))
			return (&app->common_flags[i]);
		i++;
	}
	return (NULL);
}

t_clp_result	clp_parse(int argc, char **argv)
{
	clp_print_usage(argv[0]);
	return clp_success;
}
