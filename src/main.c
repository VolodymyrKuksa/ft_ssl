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

void			append_bytes(char **dst, size_t const dst_size,
		char const *src, size_t const src_size)
{
	char	*result_bytes;

	if (!src_size)
		return ;
	if (!(result_bytes = (char*)malloc(dst_size + src_size)))
	{
		*dst = NULL;
		return ;
	}
	ft_memcpy(result_bytes, dst, dst_size);
	ft_memcpy(result_bytes + dst_size, src, src_size);
	free(*dst);
	*dst = result_bytes;
}

void			read_stdin(char** bytes, size_t* bytes_size)
{
	char	*input_buff;
	size_t	n;

	if (!(input_buff = (char*)malloc(INPUT_BUFFER_SIZE)))
	{
		ft_putendl("Failed to allocate input buffer");
		exit(1);
	}

	*bytes_size = 0;
	*bytes = (char*)malloc(*bytes_size);
	n = 1;
	while (n > 0)
	{
		n = read(0, input_buff, INPUT_BUFFER_SIZE);
		append_bytes(bytes, *bytes_size, input_buff, n);
		if (!*bytes)
		{
			ft_putendl("Memory allocation fail when reading input");
			exit(1);
		}
		*bytes_size += n;
	}

	free(input_buff);
}

char			*to_hex(unsigned char *bytes, size_t size)
{
	char	*hex_byte;
	char	*result;
	size_t	i;

	result = ft_strnew(size * 2);
	i = 0;
	while (i < size)
	{
		hex_byte = ft_itoa_base((int)(bytes[i]), 16);
		if (ft_strlen(hex_byte) != 2)
		{
			result[2 * i] = '0';
			result[(2 * i) + 1] = hex_byte[0];
		}
		else
			ft_strcpy(result + 2 * i, hex_byte);
		free(hex_byte);
		++i;
	}

	return (result);
}

//	TODO: create some func that take pointer to the algo func as a param
//		and executes the code below (md5/sha256_func are the same)
t_clp_result	md5_func(int flags, int argc, char** argv)
{
	char			*input;
	size_t			input_size;
	unsigned char	*hash;
	char			*output;

	read_stdin(&input, &input_size);
	hash = md5((unsigned char*)input, input_size);
	output = to_hex(hash, 16);
	ft_putendl(output);
	free(output);
	free(input);
	return clp_success;
}

t_clp_result	sha256_func(int flags, int argc, char** argv)
{
	char			*input;
	size_t			input_size;
	unsigned char	*hash;
	char			*output;

	read_stdin(&input, &input_size);
	hash = sha256((unsigned char*)input, input_size);
	output = to_hex(hash, 32);
	ft_putendl(output);
	free(output);
	free(input);
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
}
