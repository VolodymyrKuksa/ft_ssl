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

typedef struct	s_clp_parameter
{
	const char	*name;
	const char	*description;
}				t_clp_param;

typedef struct	s_clp_flag
{
	t_clp_param		param;
	int				value;
}				t_clp_flag;

typedef void (t_clp_cmd_func)(int flags, int param_count, char **params);

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

# endif
