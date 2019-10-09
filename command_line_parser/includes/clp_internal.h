/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clp_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 20:39:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/09/15 20:39:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLP_INTERNAL_H
# define CLP_INTERNAL_H

# include "clp.h"
# include "clp_data_types.h"

void			clp_clear_app(t_clp_app *app);
void			clp_clear_flag(t_clp_flag *flag);

t_clp_app		*clp_new_app();
t_clp_result	clp_fill_new_param(t_clp_param *param,
				const char *name, int id);
t_clp_result	clp_fill_param_description(t_clp_param *param,
				const char *description, const char *arg_description);

t_clp_result	clp_add_flag_to_array(t_clp_flag **array, int *size,
				t_clp_param *param, t_clp_flag_func func);

t_clp_result	clp_print_usage(const char *app_name);

t_clp_cmd		*clp_get_cmd(const char *name);
t_clp_cmd		*clp_get_cmd_by_id(int cmd_id);

t_clp_flag		*clp_get_cmd_flag(const char *name, t_clp_cmd *cmd);
t_clp_flag		*clp_get_cmd_flag_by_id(int flg_id, t_clp_cmd *cmd);

t_clp_flag		*clp_get_flag(const char *name);
t_clp_flag		*clp_get_flag_by_id(int flg_id);

#endif
