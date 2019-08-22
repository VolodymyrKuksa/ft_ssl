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

void	get_chunk(unsigned char* padded_message, word* chunk,
			size_t index, size_t chunk_size_bytes)
{
	size_t i;

	i = chunk_size_bytes * index;

	ft_memcpy(chunk, padded_message + i, chunk_size_bytes);
}