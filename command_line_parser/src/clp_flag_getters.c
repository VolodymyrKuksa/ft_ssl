/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clp_flg_getters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 22:32:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/10/09 22:32:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "clp.h"

extern t_clp_app	*g_app;

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

t_clp_flag		*clp_get_cmd_flag_by_id(int flg_id, t_clp_cmd *cmd)
{
	int i;

	i = 0;
	while (i < cmd->flag_count)
	{
		if (flg_id == cmd->flags[i].param.identifier)
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

t_clp_flag		*clp_get_flag_by_id(int flg_id)
{
	int i;

	i = 0;
	while (i < g_app->common_flag_count)
	{
		if (flg_id == g_app->common_flags[i].param.identifier)
			return (&g_app->common_flags[i]);
		i++;
	}
	return (NULL);
}
