/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:06:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/08/10 15:06:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

unsigned char		*sha256_hash_to_bytes(t_sha256_hash hash)
{
	unsigned char	*res;

	return (res);
}

unsigned char		*sha256(unsigned char *msg, size_t len)
{
	int				i;
	t_word			message_schedule_array[SHA256_WORDS_IN_MESSAGE_SCHEDULE];
	t_sha256_hash	hash;
	t_sha256_hash	chunk_hash;

	sha256_initialize_hash(&hash);
	i = 0;
	while (i < len / SHA256_BLOCK_SIZE)
	{
		++i;
	}
	return (sha256_hash_to_bytes(hash));
}
