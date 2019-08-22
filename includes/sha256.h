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
#define SHA256_H

#include "data_types.h"

typedef struct	s_sha256_hash
{
	word	h0;
	word	h1;
	word	h2;
	word	h3;
	word	h4;
	word	h5;
	word	h6;
	word	h7;
}				t_sha256_hash;

/*
**	sha256_constants.c
*/
word*					sha256_get_constants();
void					sha256_initialize_hash(t_sha256_hash* hash);

/*
**	sha256.c
*/
unsigned char*			sha256(unsigned char* msg, size_t len);

#endif
