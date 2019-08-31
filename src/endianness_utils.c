/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endianness_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 13:07:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/08/31 13:07:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		is_little_endian(void)
{
	t_word			test_word;

	test_word = 1;
	return (*((char*)&test_word));
}

void	reverse_bytes(unsigned char *bytes, size_t len)
{
	size_t			i;
	size_t			j;
	unsigned char	buf;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		buf = bytes[i];
		bytes[i] = bytes[j];
		bytes[j] = buf;
		++i;
		--j;
	}
}

void	reverse_endianness(unsigned char *msg, size_t len)
{
	size_t	i;
	size_t	word_size;

	i = 0;
	word_size = sizeof(t_word);
	while (i < len / word_size)
	{
		reverse_bytes(msg + i * word_size, word_size);
		++i;
	}
}
