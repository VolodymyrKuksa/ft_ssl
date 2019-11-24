/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clp_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:40:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/10/28 15:40:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include "libft.h"
#include "ft_ssl.h"

t_clp_result	process_params(int cmd_id, int flags,
				t_clp_cmd_arguments const *arg, int pos)
{
	char			*input;
	char			*output;
	size_t			input_size;
	int				fd;

	while (pos < arg->count)
	{
		fd = open(arg->vector[pos], O_RDONLY);
		if (fd == -1 || read(fd, NULL, 0) != 0)
		{
			ft_putstr("Unable to open file: ");
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
	char			*output;
	size_t			input_size;

	if (pos < arg->count)
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
	write(1, input, input_size);
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
