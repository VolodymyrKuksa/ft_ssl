/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clp_creation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 21:58:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/09/15 21:58:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
#include "libft.h"
#include "clp.h"
# include "clp_internal.h"

t_clp_app	*clp_new_app()
{
	t_clp_app	*app;

	app = (t_clp_app*)malloc(sizeof(t_clp_app));
	if (!app)
		return NULL;
	app->commands = NULL;
	app->command_count = 0;
	app->common_flags = NULL;
	app->common_flag_count = 0;
	return (app);
}

t_clp_result	clp_fill_new_param(t_clp_param *param, const char *name,
		const char *description, const char *argument_description)
{
	param->argument_description = NULL;
	if (!(param->name = ft_strdup(name)) ||
		!(param->description = ft_strdup(description)) ||
		(argument_description &&
		!(param->argument_description = ft_strdup(argument_description))))
		return (clp_memory_allocation_failure);
	return (clp_success);
}

t_clp_result	clp_fill_new_command(t_clp_cmd *cmd, const char *name,
	const char *description, const char *arg_description, t_clp_cmd_func *func)
{
	cmd->function = func;
	cmd->flag_count = 0;
	cmd->flags = NULL;
	return clp_fill_new_param(&cmd->param, name, description, arg_description);
}

t_clp_result	clp_fill_new_flag(t_clp_flag *flag, const char *name,
		const char *description, int value)
{
	flag->value = value;
	return clp_fill_new_param(&flag->param, name, description, NULL);
}
