/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_g_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:22:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/06/26 13:22:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

size_t	md5_g_function_f(size_t i)
{
	return i;
}

size_t	md5_g_function_g(size_t i)
{
	return ((5 * i + 1) % MD5_WORDS_IN_BLOCK);
}

size_t	md5_g_function_h(size_t i)
{
	return ((3 * i + 5) % MD5_WORDS_IN_BLOCK);
}

size_t	md5_g_function_i(size_t i)
{
	return ((7 * i) % MD5_WORDS_IN_BLOCK);
}

t_md5_g_function* md5_get_g_functions()
{
	static t_md5_g_function	functions[] = {
			md5_g_function_f, md5_g_function_g,
			md5_g_function_h, md5_g_function_i
	};

	return functions;
}
