/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 19:25:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/09/15 19:25:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLP_DATA_TYPES_H
# define CLP_DATA_TYPES_H

typedef enum	e_clp_result
{
	clp_success = 1 << 0,
	clp_unexpected_null_ptr = 1 << 1,
	clp_memory_allocation_failure = 1 << 2,
	clp_unknown_command_name = 1 << 3,
	clp_unknown_command_id = 1 << 4,
	clp_unknown_flag_id = 1 << 5,
	clp_flag_id_duplication = 1 << 6,
	clp_invalid_identifier = 1 << 7,
	clp_failure = 1 << 8
}				t_clp_result;

typedef struct	s_clp_parameter
{
	const char	*name;
	const char	*description;
	const char	*argument_description;
	int			identifier;
}				t_clp_param;

typedef struct	s_clp_cmd_arguments
{
	int			count;
	char		**vector;
}				t_clp_cmd_arguments;

typedef t_clp_result	(t_clp_flag_func)(int cmd, int prev_flags,
						t_clp_cmd_arguments const *arg, int pos);

typedef struct	s_clp_flag
{
	t_clp_param		param;
	t_clp_flag_func	*function;
}				t_clp_flag;

typedef t_clp_result	(t_clp_cmd_func)(int flags,
						t_clp_cmd_arguments const *arg);

typedef struct	s_clp_command
{
	t_clp_param		param;
	t_clp_flag		*flags;
	int				flag_count;
	t_clp_cmd_func	*function;
}				t_clp_cmd;

typedef struct	s_clp_app
{
	t_clp_cmd	*commands;
	int			command_count;
	t_clp_flag	*common_flags;
	int			common_flag_count;
}				t_clp_app;

#endif
