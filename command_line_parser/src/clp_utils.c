/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 22:37:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/10/09 22:37:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "clp_internal.h"

t_clp_result	clp_add_cmd_description(int identifier, const char *desc,
				const char *arg_desc)
{
	t_clp_cmd	*cmd;

	if (identifier < 0 || !(cmd = clp_get_cmd_by_id(identifier)))
		return (clp_unknown_command_id);
	return (clp_fill_param_description(&cmd->param, desc, arg_desc));
}

t_clp_result	clp_add_flag_to_array(t_clp_flag **array, int *size,
				t_clp_param *param, t_clp_flag_func func)
{
	t_clp_flag		*new_flag_array;

	if (!(new_flag_array =
		(t_clp_flag*)malloc(sizeof(t_clp_flag) * (*size + 1))))
		return (clp_memory_allocation_failure);
	ft_memcpy(new_flag_array, *array, sizeof(t_clp_flag) * *size);
	new_flag_array[*size].param = *param;
	new_flag_array[*size].function = func;
	free(*array);
	*array = new_flag_array;
	(*size)++;
	return (clp_success);
}

t_clp_result	clp_add_flg_description(int cmd_id, int flg_id,
				const char *desc, const char *arg_desc)
{
	t_clp_cmd	*cmd;
	t_clp_flag	*flg;

	cmd = NULL;
	if (cmd_id >= 0 && !(cmd = clp_get_cmd_by_id(cmd_id)))
		return (clp_unknown_command_id);
	if (!(flg = cmd ?
		clp_get_cmd_flag_by_id(flg_id, cmd) : clp_get_flag_by_id(flg_id)))
		return (clp_unknown_flag_id);
	return (clp_fill_param_description(&flg->param, desc, arg_desc));
}

void			clp_result_str_append(char **src, const char *str)
{
	char	*new_str;

	if (!*src)
		return ;
	new_str = ft_strjoin(*src, str);
	free(*src);
	*src = new_str;
}

char			*clp_get_result_string(t_clp_result result)
{
	char	*result_string;

	result_string = ft_strdup("");
	if (result == clp_success)
		clp_result_str_append(&result_string, "clp_success\n");
	if (result & clp_unexpected_null_ptr)
		clp_result_str_append(&result_string, "clp_unexpected_null_ptr\n");
	if (result & clp_memory_allocation_failure)
		clp_result_str_append(&result_string,
		"clp_memory_allocation_failure\n");
	if (result & clp_unknown_command_name)
		clp_result_str_append(&result_string, "clp_unknown_command_name\n");
	if (result & clp_unknown_command_id)
		clp_result_str_append(&result_string, "clp_unknown_command_id\n");
	if (result & clp_unknown_flag_id)
		clp_result_str_append(&result_string, "clp_unknown_flag_id\n");
	if (result & clp_flag_id_duplication)
		clp_result_str_append(&result_string, "clp_flag_id_duplication\n");
	if (result & clp_failure)
		clp_result_str_append(&result_string, "clp_failure\n");
	return (result_string);
}
