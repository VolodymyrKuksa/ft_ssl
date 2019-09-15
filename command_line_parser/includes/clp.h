/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 19:50:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/09/15 19:50:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLP_H
# define CLP_H

typedef enum	e_clp_result
{
	clp_success,
	clp_unexpected_null_ptr,
	clp_memory_allocation_failure,
	clp_unknown_command_name,
	clp_failure
}				t_clp_result;

typedef void (t_clp_cmd_func)(int flags, int param_count, char **params);

t_clp_result	clp_add_command(const char *name, const char *description,
					t_clp_cmd_func *func);

/*
**	if command_name == NULL, the flag is applied to all commands
**	command specific flags overwrite the flag value for specified command
*/
t_clp_result	clp_add_flag(const char *name, const char *description,
					const char *command_name, int value);

t_clp_result	clp_parse(int argc, char **argv);
void			clp_clear();

const char		*clp_get_result_string(t_clp_result);

# endif
