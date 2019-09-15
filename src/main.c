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
#include "clp.h"

void	md5_func(int flags, int argc, char** argv)
{
	printf("md5_func{flags: %d, argc: %d, argv: ", flags, argc);
	for (int i = 0; i < argc; ++i)
		printf(argc - i == 1 ? "%s": "%s, ", argv[i]);
	printf("}\n");
}

void	sha256_func(int flags, int argc, char** argv)
{
	printf("sha256_func{flags: %d, argc: %d, argv: ", flags, argc);
	for (int i = 0; i < argc; ++i)
		printf(argc - i == 1 ? "%s": "%s, ", argv[i]);
	printf("}\n");
}

void	check_clp_result(t_clp_result result)
{
	if (result != clp_success)
	{
		printf("CLP Error: %s\n", clp_get_result_string(result));
		exit(1);
	}
}

int		main(int argc, char **argv)
{
	t_clp_result	result;

	result = clp_add_command("md5", "Execute MD5 hashing algorithm", md5_func);
	check_clp_result(result);
	result = clp_add_command("sha256", "Execute SHA256 hashing algorithm", sha256_func);
	check_clp_result(result);
	result = clp_add_flag("-q", "Quiet mode", NULL, 1);
	check_clp_result(result);
	result = clp_add_flag("-q", "Quiet mode for md5", "md5", 2);
	check_clp_result(result);
	result = clp_parse(argc, argv);
	check_clp_result(result);
	clp_clear();
	return (0);







//	unsigned char	*msg;
//	size_t			len;
//	unsigned char	*bytes;

//	msg = (unsigned char*)ft_strdup("Quick Brown Fox Jumps Over The Lazy Dog");
//	len = ft_strlen((char*)msg);
//	bytes = md5(msg, len);
//	for (int i = 0; i < 16; ++i)
//	{
//		printf("%2.2x", bytes[i]);
//	}
//	free(bytes);
//	printf("\n");
//	bytes = sha256(msg, len);
//	for (int i = 0; i < 32; ++i)
//	{
//		printf("%2.2x", bytes[i]);
//	}
//	free(bytes);
//	printf("\n");
//	return (0);
}
