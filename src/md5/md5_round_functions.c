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

word	md5_round_function_f(word b, word c, word d)
{
	return ((b & c) | ((~b) & d));
}

word	md5_round_function_g(word b, word c, word d)
{
	return ((b & d) | ((~d) & c));
}

word	md5_round_function_h(word b, word c, word d)
{
	return (b ^ c ^ d);
}

word	md5_round_function_i(word b, word c, word d)
{
	return (c ^ (b | (~d)));
}

t_md5_round_function* md5_get_round_functions(void)
{
	static t_md5_round_function functions[] = {
			md5_round_function_f, md5_round_function_g,
			md5_round_function_h, md5_round_function_i
	};

	return functions;
}
