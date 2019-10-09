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

#include "clp_data_types.h"

/*
**	identifier has to be >= 0
*/
t_clp_result	clp_add_command(const char *name, int identifier,
				t_clp_cmd_func *func);
t_clp_result	clp_add_cmd_description(int identifier,
				const char *description, const char *arg_description);

/*
**	if cmd_id < 0, the flag is applied to all commands
**	command specific flags overwrite the flag value for specified command
**	flg_ids have to be unique!!!
**	flg_ids will be |ed together when passed into the command function
*/
t_clp_result	clp_add_flag(const char *name, int cmd_id, int flg_id,
				t_clp_flag_func *func);
t_clp_result	clp_add_flg_description(int cmd_id, int flg_id,
				const char *description, const char *arg_description);

t_clp_result	clp_parse(int argc, char **argv);
void			clp_clear();

char			*clp_get_result_string(t_clp_result result);

#endif
