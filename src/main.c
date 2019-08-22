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

#include "stdio.h"

#include "ft_ssl.h"
#include "stdlib.h"
#include "md5.h"

#include "libft.h"

int	main(void)
{
	unsigned char	*msg;
	size_t			len;
	size_t			padded_length;
	unsigned char	*padded_message;
	unsigned char	*bytes;

	msg = (unsigned char*)"The quick brown fox jumps over the lazy dog";
	len = ft_strlen((char*)msg);
	padded_message = add_message_padding(msg, len,
			&padded_length, MD5_BLOCK_SIZE);
	bytes = md5(padded_message, padded_length);
	for (int i = 0; i < 16; ++i)
	{
		printf("%2.2x", bytes[i]);
	}
	printf("\n");
	return (0);
}
