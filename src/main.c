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

#include <fcntl.h>
#include "stdio.h"//

#include "ft_ssl.h"
#include "stdlib.h"
#include "md5.h"
#include "sha256.h"

#include "libft.h"
#include "clp.h"

void			output_result_string(const char *input, const char* output,
							  int prev_flags, int cmd_id)
{
	if (prev_flags & flag_quiet)
	{
		ft_putendl(output);
	}
	else if (prev_flags & flag_reverse)
	{
		ft_putstr(output);
		ft_putstr(" \"");
		ft_putstr(input);
		ft_putendl("\"");
	}
	else
	{
		ft_putstr(cmd_id == cmd_md5 ? "MD5 (\"" : "SHA256 (\"");
		ft_putstr(input);
		ft_putstr("\") = ");
		ft_putendl(output);
	}
}

void			output_result_file(const char *input, const char* output,
							  int prev_flags, int cmd_id)
{
	if (prev_flags & flag_quiet)
	{
		ft_putendl(output);
	}
	else if (prev_flags & flag_reverse)
	{
		ft_putstr(output);
		ft_putstr(" ");
		ft_putendl(input);
	}
	else
	{
		ft_putstr(cmd_id == cmd_md5 ? "MD5 (" : "SHA256 (");
		ft_putstr(input);
		ft_putstr(") = ");
		ft_putendl(output);
	}
}

void			append_bytes(char **dst, size_t const dst_size,
		char const *src, size_t const src_size)
{
	char	*result_bytes;

	if (!src_size)
		return ;
	if (!(result_bytes = (char*)malloc(dst_size + src_size)))
	{
		free(*dst);
		*dst = NULL;
		return ;
	}
	ft_memcpy(result_bytes, *dst, dst_size);
	ft_memcpy(result_bytes + dst_size, src, src_size);
	free(*dst);
	*dst = result_bytes;
}

char*			read_fd(int fd, size_t* bytes_size)
{
	char	*input_buff;
	char	*bytes;
	size_t	n;

	if (!(input_buff = (char*)malloc(INPUT_BUFFER_SIZE)))
	{
		ft_putendl("Failed to allocate input buffer");
		exit(1);
	}

	*bytes_size = 0;
	bytes = (char*)malloc(*bytes_size);
	n = 1;
	while (n > 0)
	{
		n = read(fd, input_buff, INPUT_BUFFER_SIZE);
		append_bytes(&bytes, *bytes_size, input_buff, n);
		if (!bytes)
		{
			ft_putendl("Memory allocation fail when reading input");
			exit(1);
		}
		*bytes_size += n;
	}

	free(input_buff);
	return (bytes);
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

t_clp_result	process_params(int cmd_id, int flags,
		t_clp_cmd_arguments const* arg, int pos)
{
	char			*input;
	char 			*output;
	size_t			input_size;
	int	fd;

	while (pos < arg->count)
	{
		fd = open(arg->vector[pos], O_RDONLY);
		if (fd == -1)
		{
			ft_putstr("Unable to open file ");
			ft_putendl(arg->vector[pos]);
		}
		else
		{
			input = read_fd(fd, &input_size);
			output = execute_hash_function_by_command((unsigned char*)input,
				input_size, cmd_id);
			output_result_file(arg->vector[pos], output, flags, cmd_id);
			free(output);
			free(input);
		}
		++pos;
	}
	return (clp_success);
}

t_clp_result	cmd_func(int cmd_id, int flags,
		t_clp_cmd_arguments const *arg, int pos)
{
	char			*input;
	char 			*output;
	size_t			input_size;

	if (flags & flag_string)
		return (clp_success);
	else if (pos < arg->count)
		return (process_params(cmd_id, flags, arg, pos));
	else if (!(flags & flag_print) && !(flags & flag_string))
	{
		input = read_fd(0, &input_size);
		output = execute_hash_function_by_command((unsigned char*)input,
				input_size, cmd_id);
		ft_putendl(output);
		free(output);
		free(input);
	}
	return (clp_success);
}

t_clp_result	flg_print_func(int cmd_id, int prev_flags,
				t_clp_cmd_arguments const *arg, int *pos)
{
	char			*input;
	char			*output;
	size_t			input_size;

	(void)prev_flags;
	(void)arg;
	(void)pos;
	input = read_fd(0, &input_size);
	output = execute_hash_function_by_command((unsigned char*)input, input_size,
			cmd_id);
	if (!(prev_flags & flag_quiet))
	{
		write(1, input, input_size);
	}
	ft_putendl(output);
	free(input);
	free(output);
	return (clp_success);
}

t_clp_result	flg_string_func(int cmd_id, int prev_flags,
				t_clp_cmd_arguments const *arg, int *pos)
{
	char			*input;
	char			*output;
	size_t			input_size;

	(void)prev_flags;
	if ((*pos + 1) >= arg->count)
		return (clp_failure);
	input = ft_strdup(arg->vector[*pos + 1]);
	input_size = ft_strlen(input);
	output = execute_hash_function_by_command((unsigned char*)input, input_size,
			cmd_id);
	output_result_string(input, output, prev_flags, cmd_id);
	free(output);
	free(input);
	++(*pos);
	return (clp_success);
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
	r |= clp_add_command("md5", cmd_md5, cmd_func);
	r |= clp_add_cmd_description(cmd_md5, "Execute MD5 hashing algorithm", NULL);
	r |= clp_add_command("sha256", cmd_sha256, cmd_func);
	r |= clp_add_cmd_description(cmd_sha256, "Execute SHA256 hashing algorithm", NULL);
	r |= clp_add_flag("-p", cmd_none, flag_print, flg_print_func);
	r |= clp_add_flg_description(cmd_none, flag_print, "echo STDIN to STDOUT and append the checksum to STDOUT", NULL);
	r |= clp_add_flag("-q", cmd_none, flag_quiet, NULL);
	r |= clp_add_flg_description(cmd_none, flag_quiet, "quiet mode", NULL);
	r |= clp_add_flag("-r", cmd_none, flag_reverse, NULL);
	r |= clp_add_flg_description(cmd_none, flag_reverse, "reverse the format of the output", NULL);
	r |= clp_add_flag("-s", cmd_none, flag_string, flg_string_func);
	r |= clp_add_flg_description(cmd_none, flag_string, "print the sum of the given string", NULL);
	r = (r == clp_success) ? clp_parse(argc, argv) : r;
	if (r != clp_success) {
		process_clp_result(r);
		return (1);
	}
	clp_clear();
	return (0);
}
