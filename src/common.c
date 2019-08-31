/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 11:35:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/06/26 11:35:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "libft.h"

void	word_to_bytes(t_word w, unsigned char *bytes)
{
	bytes[3] = (w >> 24) & 0xff;
	bytes[2] = (w >> 16) & 0xff;
	bytes[1] = (w >> 8) & 0xff;
	bytes[0] = w & 0xff;
}

void	get_chunk(unsigned char const *const padded_message, t_word *chunk,
			size_t index, size_t chunk_size_bytes)
{
	size_t i;

	i = chunk_size_bytes * index;
	ft_memcpy(chunk, padded_message + i, chunk_size_bytes);
}

t_word	leftrotate(t_word w, const size_t amount)
{
	return ((w << amount) | (w >> (32 - amount)));
}

t_word	rightrotate(t_word w, const size_t amount)
{
	return ((w >> amount) | (w << (32 - amount)));
}
