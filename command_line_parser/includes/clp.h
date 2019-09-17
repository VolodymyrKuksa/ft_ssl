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
	clp_success = 1 << 0,
	clp_unexpected_null_ptr = 1 << 1,
	clp_memory_allocation_failure = 1 << 2,
	clp_unknown_command_name = 1 << 3,
	clp_failure = 1 << 4
}				t_clp_result;

typedef t_clp_result	(t_clp_cmd_func)
						(int flags, int param_count, char **params);

t_clp_result	clp_add_command(const char *name, const char *description,
					const char *arg_description, t_clp_cmd_func *func);

/*
**	if command_name == NULL, the flag is applied to all commands
**	command specific flags overwrite the flag value for specified command
*/
t_clp_result	clp_add_flag(const char *name, const char *description,
					const char *command_name, int value);

t_clp_result	clp_parse(int argc, char **argv);
void			clp_clear();

char			*clp_get_result_string(t_clp_result result);

#endif
