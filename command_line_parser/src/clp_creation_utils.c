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

#include <stdlib.h>
#include "libft.h"
#include "clp.h"
#include "clp_internal.h"

t_clp_app		*clp_new_app(void)
{
	t_clp_app	*app;

	app = (t_clp_app*)malloc(sizeof(t_clp_app));
	if (!app)
		return (NULL);
	app->commands = NULL;
	app->command_count = 0;
	app->common_flags = NULL;
	app->common_flag_count = 0;
	return (app);
}

t_clp_result	clp_fill_new_param(t_clp_param *param, const char *name,
		int id)
{
	param->description = NULL;
	param->argument_description = NULL;
	if (!(param->name = ft_strdup(name)))
		return (clp_memory_allocation_failure);
	param->identifier = id;
	return (clp_success);
}

t_clp_result	clp_fill_param_description(t_clp_param *param,
				const char *description, const char *arg_description)
{
	if ((description && !(param->description = ft_strdup(description))) ||
		(arg_description && !(param->argument_description =
		ft_strdup(arg_description))))
		return (clp_memory_allocation_failure);
	return (clp_success);
}
