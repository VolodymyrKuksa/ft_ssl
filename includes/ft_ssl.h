/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 22:36:00 by vkuksa            #+#    #+#             */
/*   Updated: 2019/06/24 22:36:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_FT_SSL_H
# define FT_SSL_FT_SSL_H

# include "data_types.h"
# include "clp.h"

typedef enum	e_command_line_flag {
	flag_print = 1 << 0,
	flag_quiet = 1 << 1,
	flag_reverse = 1 << 2,
	flag_string = 1 << 3
}				t_cmd_flag;

typedef enum	e_command_identifier {
	cmd_none = -1,
	cmd_md5,
	cmd_sha256
}				t_cmd_id;

# define INPUT_BUFFER_SIZE 2048

# define MD5_DESCR "Execute MD5 hashing algorithm"
# define SHA256_DESCR "Execute SHA256 hashing algorithm"
# define PRINT_DESCR "echo STDIN to STDOUT and append the checksum to STDOUT"
# define QUIET_DESCR "quiet mode"
# define REVERSE_DESCR "reverse the format of the output"
# define STRING_DESCR "print the sum of the given string"

/*
**	padding.c
*/
unsigned char	*add_message_padding_big_endian(unsigned char const *message,
			size_t initial_length, size_t *padded_length, size_t block_size);
unsigned char	*add_message_padding_little_endian(unsigned char const *message,
		size_t initial_length, size_t *padded_length, size_t block_size);

/*
**	common.c
*/
void			word_to_bytes(t_word w, unsigned char *bytes);
void			get_chunk(unsigned char const *padded_message, t_word *chunk,
			size_t index, size_t chunk_size_bytes);
t_word			leftrotate(t_word w, size_t amount);
t_word			rightrotate(t_word w, size_t amount);

/*
**	endianness_utils.c
*/
int				is_little_endian(void);
void			reverse_endianness(unsigned char *msg, size_t len);

/*
**	execute_hash_function.c
*/
char			*execute_hash_function_by_command(unsigned char *input,
				size_t input_size, t_cmd_id cmd);

/*
**	io.c
*/
void			output_result_string(const char *input, const char *output,
				int prev_flags, int cmd_id);
void			output_result_file(const char *input, const char *output,
				int prev_flags, int cmd_id);
char			*read_fd(int fd, size_t *bytes_size);

/*
**	clp_functions.c
*/
t_clp_result	cmd_func(int cmd_id, int flags,
				t_clp_cmd_arguments const *arg, int pos);
t_clp_result	flg_print_func(int cmd_id, int prev_flags,
				t_clp_cmd_arguments const *arg, int *pos);
t_clp_result	flg_string_func(int cmd_id, int prev_flags,
				t_clp_cmd_arguments const *arg, int *pos);

#endif
