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

t_clp_result	md5_func(int flags, int argc, char** argv)
{
	printf("md5_func{flags: %d, argc: %d, argv: ", flags, argc);
	for (int i = 0; i < argc; ++i)
		printf(argc - i == 1 ? "%s": "%s, ", argv[i]);
	printf("}\n");
	return clp_success;
}

t_clp_result	sha256_func(int flags, int argc, char** argv)
{
	printf("sha256_func{flags: %d, argc: %d, argv: ", flags, argc);
	for (int i = 0; i < argc; ++i)
		printf(argc - i == 1 ? "%s": "%s, ", argv[i]);
	printf("}\n");
	if (flags == 1)
		return clp_failure;
	return clp_success;
}

void	process_clp_result(t_clp_result result)
{
	char	*clp_error_str;

	clp_error_str = clp_get_result_string(result);
	if (!clp_error_str)
	{
		ft_putendl("Failed to parse CLP error(s)");
		return;
	}
	ft_putendl("CLP Error(s):");
	ft_putstr(clp_error_str);
	free(clp_error_str);
}

int		main(int argc, char **argv)
{
	t_clp_result	r;
//	const char		*arg_desc = "Param1 - param1 desc\n"
//								"Param2 - param2 desc\n"
//								"Param3 - param3 desc\n"
//								"Param4 - param4 desc";

	r = 0;
	r |= clp_add_command("md5", "Execute MD5 hashing algorithm", NULL, md5_func);
	r |= clp_add_command("sha256", "Execute SHA256 hashing algorithm", NULL, sha256_func);
	r |= clp_add_flag("-p", "echo STDIN to STDOUT and append the checksum to STDOUT", NULL, flag_print);
	r |= clp_add_flag("-q", "quiet mode", NULL, flag_quiet);
	r |= clp_add_flag("-r", "reverse the format of the output", NULL, flag_reverse);
	r |= clp_add_flag("-s", "print the sum of the given string", NULL, flag_string);
	r |= clp_parse(argc, argv);
	if (r != clp_success) {
		process_clp_result(r);
		return (1);
	}
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
