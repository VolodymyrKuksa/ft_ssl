/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 22:36:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/06/24 22:36:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_FT_SSL_H
# define FT_SSL_FT_SSL_H

# include "data_types.h"

/*
**	padding.c
*/
unsigned char	*add_message_padding_big_endian(unsigned char const *message,
			size_t initial_length, size_t *padded_length, size_t block_size);
unsigned char	*add_message_padding_little_endian(unsigned char const *message,
		size_t initial_length, size_t *padded_length, size_t block_size);

/*
**	common.c
*/
void			word_to_bytes(t_word w, unsigned char *bytes);
void			get_chunk(unsigned char const *padded_message, t_word *chunk,
			size_t index, size_t chunk_size_bytes);
t_word			leftrotate(t_word w, size_t amount);
t_word			rightrotate(t_word w, size_t amount);

/*
**	endianness_utils.c
*/
int				is_little_endian(void);
void			reverse_endianness(unsigned char *msg, size_t len);

#endif
