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

typedef enum	e_command_line_flags {
	flag_print = 1 << 0,
	flag_quiet = 1 << 1,
	flag_reverse = 1 << 2,
	flag_string = 1 << 3
}				t_cmd_flags;

typedef enum	e_command_identifiers {
	cmd_none = -1,
	cmd_md5,
	cmd_sha256
}				t_cmd_ids;

# define INPUT_BUFFER_SIZE 2048

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
