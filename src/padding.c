/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 11:19:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/06/26 11:19:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "libft.h"

void			length_to_bytes(unsigned long length, unsigned char* bytes)
{
	bytes[7] = (length >> 56) & 0xff;
	bytes[6] = (length >> 48) & 0xff;
	bytes[5] = (length >> 40) & 0xff;
	bytes[4] = (length >> 32) & 0xff;
	bytes[3] = (length >> 24) & 0xff;
	bytes[2] = (length >> 16) & 0xff;
	bytes[1] = (length >> 8) & 0xff;
	bytes[0] = length & 0xff;
}

unsigned char*	add_message_padding(unsigned char *message,
			size_t initial_length, size_t *padded_length, size_t block_size)
{
	unsigned char	length_bytes[sizeof(unsigned long)];
	unsigned char*	padded_message;

	length_to_bytes(initial_length * 8, length_bytes);
	*padded_length = initial_length + 1 +
		(block_size - ((initial_length + 1) % block_size));

	if(!(padded_message =
		(unsigned char*)malloc((*padded_length + 1) * sizeof(unsigned char))))
		return NULL;

	ft_memcpy(padded_message, message, initial_length);
	padded_message[initial_length] = 0x80;

	while (++initial_length < (*padded_length - sizeof(unsigned long)))
		padded_message[initial_length] = 0;

	ft_memcpy(padded_message + *padded_length - sizeof(unsigned long),
		length_bytes, sizeof(unsigned long));

	return (padded_message);
}
