/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 22:19:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/06/24 22:19:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"//

#include "ft_ssl.h"
#include "stdlib.h"
#include "md5.h"
#include "sha256.h"

#include "libft.h"

int		main(void)
{
	unsigned char	*msg;
	size_t			len;
	unsigned char	*bytes;

	msg = (unsigned char*)ft_strdup("Quick Brown Fox Jumps Over The Lazy Dog");
	len = ft_strlen((char*)msg);
	bytes = md5(msg, len);
	for (int i = 0; i < 16; ++i)
	{
		printf("%2.2x", bytes[i]);
	}
	free(bytes);
	printf("\n");
	bytes = sha256(msg, len);
	for (int i = 0; i < 32; ++i)
	{
		printf("%2.2x", bytes[i]);
	}
	free(bytes);
	printf("\n");
	return (0);
}
