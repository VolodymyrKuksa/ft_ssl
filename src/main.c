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

void			read_fd(int fd, char** bytes, size_t* bytes_size)
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
		n = read(fd, input_buff, INPUT_BUFFER_SIZE);
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

char		*execute_hash_function(unsigned char* input, size_t input_size,
			unsigned char* (*f)(const unsigned char*, size_t), size_t hash_size)
{
	unsigned char	*hash;
	char			*output;

	hash = f(input, input_size);
	output = to_hex(hash, hash_size);
	free(hash);
	return (output);
}

char		*execute_hash_function_by_command(unsigned char *input,
			size_t input_size, t_cmd_id cmd)
{
	static size_t			s_hash_size[] = {16, 32};
	static unsigned char	*(*s_function[])(const unsigned char*, size_t) =
							{md5, sha256};
	unsigned char			*hash;
	char					*output;

	hash = s_function[cmd](input, input_size);
	output = to_hex(hash, s_hash_size[cmd]);
	free(hash);
	return (output);
}

t_clp_result	md5_func(int flags, t_clp_cmd_arguments const *arg, int pos)
{
	char			*input;
	char 			*output;
	size_t			input_size;

	read_fd(0, &input, &input_size);
	output = execute_hash_function((unsigned char*)input, input_size, md5, 16);
//	ft_putendl(output);
	free(output);
	free(input);
	return clp_success;
}

t_clp_result	sha256_func(int flags, t_clp_cmd_arguments const *arg, int pos)
{
	char			*input;
	char 			*output;
	size_t			input_size;

	read_fd(0, &input, &input_size);
	output = execute_hash_function((unsigned char*)input, input_size, sha256, 32);
//	ft_putendl(output);
	free(output);
	free(input);
	return clp_success;
}

t_clp_result	flg_func(int cmd_id, int prev_flags,
				t_clp_cmd_arguments const *arg, int pos)
{
	printf("<%s>{prev_flags: [ ", arg->vector[pos]);
	if (prev_flags & flag_print)
		printf("-p ");
	if (prev_flags & flag_quiet)
		printf("-q ");
	if (prev_flags & flag_reverse)
		printf("-r ");
	if (prev_flags & flag_string)
		printf("-s ");
	printf("] cmd: %d; pos: %d}\n", cmd_id, pos);
	return clp_success;
}

t_clp_result	flg_print_func(int cmd_id, int prev_flags,
				t_clp_cmd_arguments const *arg, int pos)
{
	char			*input;
	char			*output;
	size_t			input_size;

	(void)prev_flags;
	(void)arg;
	(void)pos;
	read_fd(0, &input, &input_size);
	output = execute_hash_function_by_command((unsigned char*)input, input_size,
			cmd_id);
	write(1, input, input_size);
	ft_putendl(output);
	free(input);
	free(output);
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
	r |= clp_add_command("md5", cmd_md5, md5_func);
	r |= clp_add_cmd_description(cmd_md5, "Execute MD5 hashing algorithm", NULL);
	r |= clp_add_command("sha256", cmd_sha256, sha256_func);
	r |= clp_add_cmd_description(cmd_sha256, "Execute SHA256 hashing algorithm", NULL);
	r |= clp_add_flag("-p", cmd_none, flag_print, flg_print_func);
	r |= clp_add_flg_description(cmd_none, flag_print, "echo STDIN to STDOUT and append the checksum to STDOUT", NULL);
	r |= clp_add_flag("-q", cmd_none, flag_quiet, flg_func);
	r |= clp_add_flg_description(cmd_none, flag_quiet, "quiet mode", NULL);
	r |= clp_add_flag("-r", cmd_none, flag_reverse, flg_func);
	r |= clp_add_flg_description(cmd_none, flag_reverse, "reverse the format of the output", NULL);
	r |= clp_add_flag("-s", cmd_none, flag_string, flg_func);
	r |= clp_add_flg_description(cmd_none, flag_string, "print the sum of the given string", NULL);
	r = (r == clp_success) ? clp_parse(argc, argv) : r;
	if (r != clp_success) {
		process_clp_result(r);
		return (1);
	}
	clp_clear();
	return (0);
}
