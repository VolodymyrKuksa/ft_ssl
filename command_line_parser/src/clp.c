/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 20:14:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/09/15 20:14:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "clp.h"
#include "clp_internal.h"

t_clp_app	*g_app = NULL;

t_clp_result	clp_add_command(const char *name, int id,
				t_clp_cmd_func *func)
{
	t_clp_result	fill_result;
	t_clp_cmd		*new_cmd_array;

	if (!name || id < 0 || !func)
		return (id < 0 ? clp_invalid_identifier : clp_unexpected_null_ptr);
	if ((!g_app && !(g_app = clp_new_app())) ||
		(!(new_cmd_array = (t_clp_cmd*)malloc(sizeof(t_clp_cmd) *
		(g_app->command_count + 1)))))
		return (clp_memory_allocation_failure);
	ft_memcpy(new_cmd_array, g_app->commands, sizeof(t_clp_cmd) *
			g_app->command_count);
	fill_result = clp_fill_new_param(&new_cmd_array[g_app->command_count].param,
			name, id);
	if (fill_result != clp_success)
	{
		free(new_cmd_array);
		return (fill_result);
	}
	new_cmd_array[g_app->command_count].function = func;
	new_cmd_array[g_app->command_count].flags = NULL;
	new_cmd_array[g_app->command_count].flag_count = 0;
	free(g_app->commands);
	g_app->commands = new_cmd_array;
	g_app->command_count++;
	return (clp_success);
}

int				clp_is_unique_flag_id(int flg_id)
{
	int i;

	if (clp_get_flag_by_id(flg_id))
		return (0);
	i = 0;
	while (i < g_app->command_count)
	{
		if (clp_get_cmd_flag_by_id(flg_id, &g_app->commands[i]))
			return (0);
		++i;
	}
	return (1);
}

t_clp_result	clp_add_flag(const char *name, int cmd_id, int flg_id,
				t_clp_flag_func *func)
{
	t_clp_cmd		*cmd;
	t_clp_param		new_param;
	t_clp_result	err;

	if (!clp_is_unique_flag_id(flg_id))
		return (clp_flag_id_duplication);
	err = clp_fill_new_param(&new_param, name, flg_id);
	if (err != clp_success)
		return (err);
	if (cmd_id < 0)
	{
		return (clp_add_flag_to_array(&g_app->common_flags,
			&g_app->common_flag_count, &new_param, func));
	}
	if (!(cmd = clp_get_cmd_by_id(cmd_id)))
		return (clp_unknown_command_id);
	return (clp_add_flag_to_array(&cmd->flags,
			&cmd->flag_count, &new_param, func));
}
