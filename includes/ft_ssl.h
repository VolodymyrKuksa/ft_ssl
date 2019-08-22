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

//	TODO: Remove this shit
# define LEFTROTATE(x, c)	(((x) << (c)) | ((x) >> (32 - (c))))
# define RIGHTROTATE(x, c)	(((x) >> (c)) | ((x) << (32 - (c))))

/*
**	padding.c
*/
unsigned char	*add_message_padding(unsigned char *message,
			size_t initial_length, size_t *padded_length, size_t block_size);

/*
**	common.c
*/
void			word_to_bytes(t_word w, unsigned char *bytes);
void			get_chunk(unsigned char *padded_message, t_word *chunk,
			size_t index, size_t chunk_size_bytes);

#endif
