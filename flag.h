/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:15:59 by yfarini           #+#    #+#             */
/*   Updated: 2022/08/24 17:25:26 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAG_H
# define FLAG_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <assert.h>
# include <limits.h>
# include <string.h>
# include <errno.h>

typedef int8_t			(*t_flag_handler)(const char *, const char *, void *);
typedef struct s_flag_option
{
	const char		*name;
	void			*var;
	const char		*description;
	unsigned int	flags;
	char			shorthand;
	t_flag_handler	handler;
}						t_flag_option;

# define FL_IS_BOOLEAN 1

# ifndef F_MAX_FLAGS
#  define F_MAX_FLAGS 256
# endif

int64_t	flag_def_int64(t_flag_option option, int64_t default_val);
int32_t	flag_def_int32(t_flag_option option, int32_t default_val);
int16_t	flag_def_int16(t_flag_option option, int16_t default_val);
int8_t	flag_def_int8(t_flag_option option, int8_t default_val);
int8_t	flag_def_bool(t_flag_option option, int8_t default_val);
char	flag_def_char(t_flag_option option, char default_val);
void	flag_define(t_flag_option option);
void	flag_usage(int fd);
int		flag_parse(int argc, char ***argv);
char	*flag_get_error(void);

#endif
