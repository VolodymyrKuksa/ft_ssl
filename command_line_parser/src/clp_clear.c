/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clp_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 20:50:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/09/15 20:50:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include "clp_internal.h"

void	clp_clear_parameter(t_clp_param *param)
{
	if (param->name)
	{
		free((void*)param->name);
		param->name = NULL;
	}
	if (param->description)
	{
		free((void*)param->description);
		param->description = NULL;
	}
	if (param->argument_description)
	{
		free((void *) param->argument_description);
		param->argument_description = NULL;
	}
}

void	clp_clear_command(t_clp_cmd *cmd)
{
	int i;

	i = 0;
	while (i < cmd->flag_count)
		clp_clear_flag(&cmd->flags[i++]);
	free(cmd->flags);
	cmd->flags = NULL;
	clp_clear_parameter(&cmd->param);
}

void	clp_clear_flag(t_clp_flag *flag)
{
	clp_clear_parameter(&flag->param);
	flag->value = 0;
}

void	clp_clear_app(t_clp_app *app)
{
	int i;

	i = 0;
	while (i < app->command_count)
		clp_clear_command(&app->commands[i++]);
	free(app->commands);
	app->commands = NULL;
	app->command_count = 0;
	i = 0;
	while (i < app->common_flag_count)
		clp_clear_flag(&app->common_flags[i++]);
	free(app->common_flags);
	app->common_flags = NULL;
	app->common_flag_count = 0;
}
