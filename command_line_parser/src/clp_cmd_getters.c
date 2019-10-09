/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clp_cmd_getters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 22:30:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/10/09 22:30:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "clp.h"

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

t_clp_cmd		*clp_get_cmd_by_id(int id)
{
	int i;

	i = 0;
	while (i < g_app->command_count)
	{
		if (id == g_app->commands[i].param.identifier)
			return (&g_app->commands[i]);
		i++;
	}
	return (NULL);
}
