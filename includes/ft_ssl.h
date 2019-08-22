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
#define FT_SSL_FT_SSL_H

#include "data_types.h"

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

/*
**	padding.c
*/
unsigned char*	add_message_padding(unsigned char *message,
			size_t initial_length, size_t *padded_length, size_t block_size);

/*
**	common.c
*/
void			get_chunk(unsigned char* padded_message, word* chunk,
			size_t index, size_t chunk_size_bytes);

#endif
