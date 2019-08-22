/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:07:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/08/10 15:07:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include "data_types.h"

typedef struct			s_sha256_hash
{
	t_word	h0;
	t_word	h1;
	t_word	h2;
	t_word	h3;
	t_word	h4;
	t_word	h5;
	t_word	h6;
	t_word	h7;
}						t_sha256_hash;

# define SHA256_BLOCK_SIZE 64
# define SHA256_WORDS_IN_BLOCK 16
# define SHA256_MESSAGE_SCHEDULE_SIZE 256
# define SHA256_WORDS_IN_MESSAGE_SCHEDULE 64

/*
**	sha256_constants.c
*/
t_word					*sha256_get_constants();
void					sha256_initialize_hash(t_sha256_hash *hash);

/*
**	sha256.c
*/
unsigned char			*sha256(unsigned char *msg, size_t len);

#endif
