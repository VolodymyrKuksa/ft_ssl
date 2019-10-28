/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 22:19:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/06/24 22:19:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include "libft.h"
#include "ft_ssl.h"

void	process_clp_result(t_clp_result result)
{
	char	*clp_error_str;

	clp_error_str = clp_get_result_string(result);
	if (!clp_error_str)
	{
		ft_putendl("Failed to parse CLP error(s)");
		return ;
	}
	ft_putendl("CLP Error(s):");
	ft_putstr(clp_error_str);
	free(clp_error_str);
}

int		main(int argc, char **argv)
{
	t_clp_result	r;

	r = 0;
	r |= clp_add_command("md5", cmd_md5, cmd_func);
	r |= clp_add_cmd_description(cmd_md5, MD5_DESCR, NULL);
	r |= clp_add_command("sha256", cmd_sha256, cmd_func);
	r |= clp_add_cmd_description(cmd_sha256, SHA256_DESCR, NULL);
	r |= clp_add_flag("-p", cmd_none, flag_print, flg_print_func);
	r |= clp_add_flg_description(cmd_none, flag_print, PRINT_DESCR, NULL);
	r |= clp_add_flag("-q", cmd_none, flag_quiet, NULL);
	r |= clp_add_flg_description(cmd_none, flag_quiet, QUIET_DESCR, NULL);
	r |= clp_add_flag("-r", cmd_none, flag_reverse, NULL);
	r |= clp_add_flg_description(cmd_none, flag_reverse, REVERSE_DESCR, NULL);
	r |= clp_add_flag("-s", cmd_none, flag_string, flg_string_func);
	r |= clp_add_flg_description(cmd_none, flag_string, STRING_DESCR, NULL);
	r = (r == clp_success) ? clp_parse(argc, argv) : r;
	if (r != clp_success)
	{
		process_clp_result(r);
		return (1);
	}
	clp_clear();
	return (0);
}
