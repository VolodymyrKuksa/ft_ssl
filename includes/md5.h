/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 08:28:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/06/26 08:28:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include "data_types.h"

typedef struct			s_md5_hash
{
	t_word	h0;
	t_word	h1;
	t_word	h2;
	t_word	h3;
}						t_md5_hash;

typedef	t_word(*t_md5_round_function)(t_word, t_word, t_word);
typedef	size_t(*t_md5_g_function)(size_t);

/*
**	512 bit block converted to bytes
*/
# define MD5_BLOCK_SIZE 64
# define MD5_WORDS_IN_BLOCK 16

/*
**	md5_round_functions.c
*/
t_md5_round_function	*md5_get_round_functions(void);

/*
**	md5_g_functions.c
*/
t_md5_g_function		*md5_get_g_functions();

/*
**	md5_constants.c
*/
t_word					*md5_get_constants();
size_t					md5_get_rotation_amount(size_t i);
void					md5_initialize_hash(t_md5_hash *hash);

/*
**	md5.c
*/
unsigned char			*md5(unsigned char const *msg, size_t len);

#endif
