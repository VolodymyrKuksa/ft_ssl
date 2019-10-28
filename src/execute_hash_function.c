/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_hash_function.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:29:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/10/28 15:29:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"
#include "md5.h"
#include "sha256.h"

char		*to_hex(unsigned char *bytes, size_t size)
{
	char	*hex_byte;
	char	*result;
	size_t	i;

	result = ft_strnew(size * 2);
	i = 0;
	while (i < size)
	{
		hex_byte = ft_itoa_base((int)(bytes[i]), 16);
		if (ft_strlen(hex_byte) != 2)
		{
			result[2 * i] = '0';
			result[(2 * i) + 1] = hex_byte[0];
		}
		else
			ft_strcpy(result + 2 * i, hex_byte);
		free(hex_byte);
		++i;
	}
	return (result);
}

char		*execute_hash_function_by_command(unsigned char *input,
			size_t input_size, t_cmd_id cmd)
{
	static size_t			s_hash_size[] = {16, 32};
	static unsigned char	*(*s_function[])(const unsigned char*, size_t) =
	{md5, sha256};
	unsigned char			*hash;
	char					*output;

	hash = s_function[cmd](input, input_size);
	output = to_hex(hash, s_hash_size[cmd]);
	free(hash);
	return (output);
}
