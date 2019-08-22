/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 08:27:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/06/26 08:27:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

t_word					md5_round_function_f(t_word b, t_word c, t_word d)
{
	return ((b & c) | ((~b) & d));
}

t_word					md5_round_function_g(t_word b, t_word c, t_word d)
{
	return ((b & d) | ((~d) & c));
}

t_word					md5_round_function_h(t_word b, t_word c, t_word d)
{
	return (b ^ c ^ d);
}

t_word					md5_round_function_i(t_word b, t_word c, t_word d)
{
	return (c ^ (b | (~d)));
}

t_md5_round_function	*md5_get_round_functions(void)
{
	static t_md5_round_function functions[] = {
			md5_round_function_f, md5_round_function_g,
			md5_round_function_h, md5_round_function_i
	};

	return (functions);
}
