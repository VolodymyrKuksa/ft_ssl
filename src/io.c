/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:36:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/10/28 15:36:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"

void			output_result_string(const char *input, const char *output,
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

void			output_result_file(const char *input, const char *output,
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

char			*read_fd(int fd, size_t *bytes_size)
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
