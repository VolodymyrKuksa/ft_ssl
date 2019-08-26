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

#include <libft.h>
#include "ft_ssl.h"
#include "sha256.h"

unsigned char		*sha256_hash_to_bytes(t_sha256_hash hash)
{
	unsigned char	*result;

	if (!(result = (unsigned char*)malloc(sizeof(t_sha256_hash))))
		return (NULL);
	word_to_bytes(hash.h0, result);
	word_to_bytes(hash.h1, result + sizeof(t_word));
	word_to_bytes(hash.h2, result + sizeof(t_word) * 2);
	word_to_bytes(hash.h3, result + sizeof(t_word) * 3);
	word_to_bytes(hash.h4, result + sizeof(t_word) * 4);
	word_to_bytes(hash.h5, result + sizeof(t_word) * 5);
	word_to_bytes(hash.h6, result + sizeof(t_word) * 6);
	word_to_bytes(hash.h7, result + sizeof(t_word) * 7);
	return (result);
}

void				sha256_extend_message(t_word *message)
{
	int		i;
	t_word	s0;
	t_word	s1;

	i = 16;
	while (i < 64)
	{
		s0 = rightrotate(message[i - 15], 7) ^ rightrotate(message[i -15], 18) ^
				(message[i - 15] >> 3);
		s1 = rightrotate(message[i - 2], 17) ^ rightrotate(message[i - 2], 19) ^
				(message[i - 2] >> 10);
		message[i] = message[i - 16] + s0 + message[i - 7] + s1;
		++i;
	}
}

t_sha256_hash		sha256_process_chunk(
						const t_word *chunk, t_sha256_hash hash)
{
	int		i;
	t_word	message[SHA256_WORDS_IN_MESSAGE_SCHEDULE];

	ft_memcpy(message, chunk, SHA256_WORDS_IN_BLOCK);
	sha256_extend_message(message);
	i = 0;
	while (i < 64)
	{
		//	TODO: Main logic here
		++i;
	}
	return hash;
}

unsigned char		*sha256(unsigned char *msg, size_t len)
{
	int				i;
	t_word			chunk[SHA256_WORDS_IN_BLOCK];
	t_sha256_hash	hash;
	t_sha256_hash	chunk_hash;

	sha256_initialize_hash(&hash);
	i = 0;
	while (i < len / SHA256_BLOCK_SIZE)
	{
		get_chunk(msg, chunk, i, SHA256_BLOCK_SIZE);
		chunk_hash = sha256_process_chunk(chunk, hash);
		hash.h0 += chunk_hash.h0;
		hash.h1 += chunk_hash.h1;
		hash.h2 += chunk_hash.h2;
		hash.h3 += chunk_hash.h3;
		hash.h4 += chunk_hash.h4;
		hash.h5 += chunk_hash.h5;
		hash.h6 += chunk_hash.h6;
		hash.h7 += chunk_hash.h7;
		++i;
	}
	return (sha256_hash_to_bytes(hash));
}
