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

# include <stdlib.h>
#include "libft.h"
# include "clp.h"
# include "clp_internal.h"

t_clp_app	*app = NULL;

t_clp_result	clp_add_command(const char *name, const char *description,
						const char *arg_description, t_clp_cmd_func *func)
{
	t_clp_result	fill_result;
	t_clp_cmd		*new_cmd_array;

	if (!name || !description || !func)
		return (clp_unexpected_null_ptr);
	if (!app && !(app = clp_new_app()))
		return (clp_memory_allocation_failure);
	if (!(new_cmd_array = (t_clp_cmd*)malloc(sizeof(t_clp_cmd) *
			(app->command_count + 1))))
		return (clp_memory_allocation_failure);
	ft_memcpy(new_cmd_array, app->commands, sizeof(t_clp_cmd) *
			app->command_count);
	fill_result = clp_fill_new_command(&new_cmd_array[app->command_count], name,
			description, arg_description, func);
	if (fill_result != clp_success)
	{
		free(new_cmd_array);
		return (fill_result);
	}
	free(app->commands);
	app->commands = new_cmd_array;
	app->command_count++;
	return (clp_success);
}

t_clp_result	clp_add_flag_to_array(t_clp_flag **array, int *size,
		t_clp_param *param, int value)
{
	t_clp_result	fill_result;
	t_clp_flag		*new_flag_array;

	if (!(new_flag_array =
			(t_clp_flag*)malloc(sizeof(t_clp_flag) * (*size + 1))))
		return (clp_memory_allocation_failure);
	ft_memcpy(new_flag_array, *array, sizeof(t_clp_flag) * *size);
	fill_result = clp_fill_new_flag(&new_flag_array[*size], param->name,
			param->description, value);
	if (fill_result != clp_success)
	{
		free(new_flag_array);
		return (fill_result);
	}
	free(*array);
	*array = new_flag_array;
	(*size)++;
	return (clp_success);
}

t_clp_result	clp_add_flag(const char *name, const char *description,
					const char *command_name, int value)
{
	t_clp_cmd	*cmd;
	t_clp_param	new_param;

	new_param.name = name;
	new_param.description = description;
	if (!command_name)
		return (clp_add_flag_to_array(&app->common_flags,
				&app->common_flag_count, &new_param, value));
	if (!(cmd = clp_get_cmd(command_name)))
		return (clp_unknown_command_name);
	return (clp_add_flag_to_array(&cmd->flags,
			&cmd->flag_count, &new_param, value));
}

void			clp_clear(void)
{
	if (app)
	{
		clp_clear_app(app);
		free(app);
		app = NULL;
	}
}

void			clp_result_str_append(char **src, const char *str)
{
	char	*new_str;
	
	if (!*src)
		return;
	new_str = ft_strjoin(*src, str);
	free(*src);
	*src = new_str;
}

char			*clp_get_result_string(t_clp_result result)
{
	char	*result_string;
	
	result_string = ft_strdup("");
	if (result & clp_success)
		clp_result_str_append(&result_string, "clp_success\n");
	if (result & clp_unexpected_null_ptr)
		clp_result_str_append(&result_string, "clp_unexpected_null_ptr\n");
	if (result & clp_memory_allocation_failure)
		clp_result_str_append(&result_string,
				"clp_memory_allocation_failure\n");
	if (result & clp_unknown_command_name)
		clp_result_str_append(&result_string, "clp_unknown_command_name\n");
	if (result & clp_failure)
		clp_result_str_append(&result_string, "clp_failure\n");
	return (result_string);
}
