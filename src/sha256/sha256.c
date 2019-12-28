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

void				sha256_extend_message(t_word *message, const t_word *chunk)
{
	int		i;
	t_word	s0;
	t_word	s1;

	ft_memcpy(message, chunk, SHA256_BLOCK_SIZE);
	i = 16;
	while (i < 64)
	{
		s0 = rightrotate(message[i - 15], 7) ^ rightrotate(message[i - 15], 18)
				^ (message[i - 15] >> 3);
		s1 = rightrotate(message[i - 2], 17) ^ rightrotate(message[i - 2], 19)
				^ (message[i - 2] >> 10);
		message[i] = message[i - 16] + s0 + message[i - 7] + s1;
		++i;
	}
}

t_sha256_hash		sha256_process_chunk(
						const t_word *chunk, t_sha256_hash hash)
{
	int		i;
	t_word	message[SHA256_WORDS_IN_MESSAGE_SCHEDULE];
	t_word	temp1;
	t_word	temp2;

	sha256_extend_message(message, chunk);
	i = -1;
	while (++i < 64)
	{
		temp1 = hash.h7 + (rightrotate(hash.h4, 6) ^ rightrotate(hash.h4, 11) ^
		rightrotate(hash.h4, 25)) + ((hash.h4 & hash.h5) ^ ((~hash.h4) &
		hash.h6)) + sha256_get_constants()[i] + message[i];
		temp2 = (rightrotate(hash.h0, 2) ^ rightrotate(hash.h0, 13) ^
		rightrotate(hash.h0, 22)) + ((hash.h0 & hash.h1) ^ (hash.h0 & hash.h2) ^
		(hash.h1 & hash.h2));
		hash.h7 = hash.h6;
		hash.h6 = hash.h5;
		hash.h5 = hash.h4;
		hash.h4 = hash.h3 + temp1;
		hash.h3 = hash.h2;
		hash.h2 = hash.h1;
		hash.h1 = hash.h0;
		hash.h0 = temp1 + temp2;
	}
	return (hash);
}

unsigned char		*sha256_main_logic(unsigned char const *const msg,
		size_t len)
{
	size_t			i;
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

unsigned char		*sha256(unsigned char const *const msg, size_t len)
{
	unsigned char	*message;
	unsigned char	*padded_message;
	size_t			padded_length;
	unsigned char	*result;
	int				endianness;

	endianness = is_little_endian();
	if (!(message = (unsigned char*)malloc(len)))
		return (NULL);
	ft_memcpy(message, msg, len);
	padded_message = add_message_padding_big_endian(message, len,
			&padded_length, SHA256_BLOCK_SIZE);
	if (endianness)
		reverse_endianness(padded_message, len + sizeof(t_word));
	result = sha256_main_logic(padded_message, padded_length);
	free(padded_message);
	free(message);
	if (endianness)
		reverse_endianness(result, 32);
	return (result);
}
