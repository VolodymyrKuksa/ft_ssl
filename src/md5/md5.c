/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 08:27:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/06/26 08:27:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

#include "libft.h"

unsigned char	*md5_hash_to_bytes(t_md5_hash hash)
{
	unsigned char	*result;

	if (!(result = (unsigned char*)malloc(sizeof(t_md5_hash))))
		return (NULL);
	word_to_bytes(hash.h0, result);
	word_to_bytes(hash.h1, result + sizeof(t_word));
	word_to_bytes(hash.h2, result + sizeof(t_word) * 2);
	word_to_bytes(hash.h3, result + sizeof(t_word) * 3);
	return (result);
}

t_md5_hash		md5_process_chunk(const t_word *chunk, t_md5_hash hash)
{
	size_t	i;
	size_t	g;
	t_word	f;

	i = 0;
	while (i < 64)
	{
		f = md5_get_round_functions()[i / 16]
			(hash.h1, hash.h2, hash.h3);
		g = md5_get_g_functions()[i / 16](i);
		f = f + hash.h0 + md5_get_constants()[i] + chunk[g];
		hash.h0 = hash.h3;
		hash.h3 = hash.h2;
		hash.h2 = hash.h1;
		hash.h1 += leftrotate(f, md5_get_rotation_amount(i));
		++i;
	}
	return (hash);
}

unsigned char	*md5_main_logic(unsigned char const *const msg, size_t len)
{
	size_t		i;
	t_word		chunk[MD5_WORDS_IN_BLOCK];
	t_md5_hash	hash;
	t_md5_hash	chunk_hash;

	md5_initialize_hash(&hash);
	i = 0;
	while (i < len / MD5_BLOCK_SIZE)
	{
		get_chunk(msg, chunk, i, MD5_BLOCK_SIZE);
		chunk_hash = md5_process_chunk(chunk, hash);
		hash.h0 += chunk_hash.h0;
		hash.h1 += chunk_hash.h1;
		hash.h2 += chunk_hash.h2;
		hash.h3 += chunk_hash.h3;
		++i;
	}
	return (md5_hash_to_bytes(hash));
}

unsigned char	*md5(unsigned char const *const msg, size_t len)
{
	unsigned char	*message;
	unsigned char	*result;

	if (!(message = ft_memalloc(len)))
		return (NULL);
	ft_memcpy(message, msg, len);
	if (!is_little_endian())
		reverse_endianness(message, len);
	result = md5_main_logic(message, len);
	free(message);
	return (result);
}
