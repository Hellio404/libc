/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:13:30 by yfarini           #+#    #+#             */
/*   Updated: 2022/08/24 17:24:05 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flag.h"

static uint32_t			g_flags_def_counter = 0;
static t_flag_option	g_flags_def[F_MAX_FLAGS];

static int8_t	flag_int64_handler(
	char const *arg,
	char const *value,
	void *dst)
{
	char		*end;
	int64_t		tmp_val;

	(void)arg;
	errno = 0;
	tmp_val = strtol(value, &end, 0);
	if (errno != 0 || *end != '\0')
		return (1);
	*(int64_t *)dst = tmp_val;
	return (0);
}

static int8_t	flag_int32_handler(
	char const *arg,
	char const *value,
	void *dst)
{
	char		*end;
	int64_t		tmp_val;

	(void)arg;
	errno = 0;
	tmp_val = strtol(value, &end, 0);
	if (errno != 0 || tmp_val > INT32_MAX
		|| tmp_val < INT32_MIN || *end != '\0')
		return (1);
	*(int32_t *)dst = (int32_t)tmp_val;
	return (0);
}

static int8_t	flag_int16_handler(
	char const *arg,
	char const *value,
	void *dst)
{
	char		*end;
	int64_t		tmp_val;

	(void)arg;
	errno = 0;
	tmp_val = strtol(value, &end, 0);
	if (errno != 0 || tmp_val > INT16_MAX
		|| tmp_val < INT16_MIN || *end != '\0')
		return (1);
	*(int16_t *)dst = (int16_t)tmp_val;
	return (0);
}

static int8_t	flag_int8_handler(
	char const *arg,
	char const *value,
	void *dst)
{
	char		*end;
	int64_t		tmp_val;

	(void)arg;
	errno = 0;
	tmp_val = strtol(value, &end, 0);
	if (errno != 0 || tmp_val > INT8_MAX || tmp_val < INT8_MIN || *end != '\0')
		return (1);
	*(int8_t *)dst = (int8_t)tmp_val;
	return (0);
}

static int8_t	flag_char_handler(const char *arg, const char *val, void *var)
{
	(void)arg;
	if (strlen(val) != 1)
		return (1);
	*(char *)var = *val;
	return (0);
}

static int8_t	flag_bool_handler(const char *arg, const char *val, void *var)
{
	(void)arg;
	if (val == NULL)
	{
		*(int8_t *)var = 1;
		return (0);
	}
	if (strcasecmp(val, "true") == 0)
		*(int8_t *)var = 1;
	else if (strcasecmp(val, "false") == 0)
		*(int8_t *)var = 0;
	else
		return (1);
	return (0);
}

int64_t	flag_def_int64(t_flag_option options, int64_t default_value)
{
	options.handler = flag_int64_handler;
	flag_define(options);
	return (default_value);
}

int32_t	flag_def_int32(t_flag_option options, int32_t default_value)
{
	options.handler = flag_int32_handler;
	flag_define(options);
	return (default_value);
}

int16_t	flag_def_int16(t_flag_option options, int16_t default_value)
{
	options.handler = flag_int16_handler;
	flag_define(options);
	return (default_value);
}

int8_t	flag_def_int8(t_flag_option options, int8_t default_value)
{
	options.handler = flag_int8_handler;
	flag_define(options);
	return (default_value);
}

int8_t	flag_def_bool(t_flag_option options, int8_t default_value)
{
	options.handler = flag_bool_handler;
	flag_define(options);
	return (default_value);
}

char	flag_def_char(t_flag_option options, char default_value)
{
	options.handler = flag_char_handler;
	flag_define(options);
	return (default_value);
}

void	flag_define(t_flag_option options)
{
	uint32_t	i;

	i = 0;
	assert(strlen(options.name) > 0 && "The name is required");
	while (i < g_flags_def_counter)
	{
		assert(
			strcmp(g_flags_def[i].name, options.name) != 0
			&& (options.shorthand == 0
				|| g_flags_def[i].shorthand != options.shorthand)
			&& "Flags should have a unique name and shorthand"
			);
		++i;
	}
	g_flags_def[g_flags_def_counter++] = options;
}

void	flag_usage(int fd)
{
	uint32_t	i;

	i = 0;
	while (i < g_flags_def_counter)
	{
		write(fd, "--", 2);
		write(fd, g_flags_def[i].name, strlen(g_flags_def[i].name));
		if (g_flags_def[i].shorthand != '\0')
		{
			write(fd, ", -", 3);
			write(fd, &g_flags_def[i].shorthand, 1);
		}
		write(fd, "\n\t", 2);
		write(fd, g_flags_def[i].description,
			strlen(g_flags_def[i].description));
		write(fd, "\n\n", 2);
		++i;
	}
}

static int	_find_arg_index(const char *name, char shorthand)
{
	uint32_t	i;

	i = 0;
	while (i < g_flags_def_counter)
	{
		if ((name != NULL && strcmp(name, g_flags_def[i].name) == 0)
			|| (shorthand != 0 && shorthand == g_flags_def[i].shorthand))
			return (i);
		++i;
	}
	return (-1);
}

char	*flag_get_error(void)
{
	static char	error[1024];

	return (error);
}

static int	flag_parse_handle_equal(
	char *flag,
	char *equal_pos,
	int flag_index)
{
	int	ret;

	*equal_pos = '\0';
	ret = g_flags_def[flag_index].handler(
			flag, equal_pos + 1,
			g_flags_def[flag_index].var);
	*equal_pos = '=';
	return (ret);
}

int	flag_parse_multi_flag(int argc, char **argv, int *i)
{
	int		j;
	int		flag_index;
	int		ret;

	j = 1;
	while (argv[*i][j])
	{
		flag_index = _find_arg_index(NULL, argv[*i][j]);
		if (flag_index == -1)
		{
			sprintf(flag_get_error(), "The flag '-%c` is invalid",  argv[*i][j]);
			return (1);
		}
		if (argv[*i][j + 1] == '=')
		{
			ret = flag_parse_handle_equal(argv[*i], &argv[*i][j + 1], flag_index);
			break;
		}
		else if ((g_flags_def[flag_index].flags & FL_IS_BOOLEAN )== 0 && argc <= *i + 1)
		{
			sprintf(flag_get_error(), "Missing value for the flag '-%c`",  argv[*i][j]);
			return (1);
		}
		else if ((g_flags_def[flag_index].flags & FL_IS_BOOLEAN )== 0)
		{
			ret = g_flags_def[flag_index].handler(argv[*i], argv[*i + 1], g_flags_def[flag_index].var);
			if (ret == 0)
				*i += 1;
			break;
		}
		else
			ret = g_flags_def[flag_index].handler(argv[*i], NULL, g_flags_def[flag_index].var);
		
		if (ret != 0)
			break ;
		++j;
	}
	if (ret != 0)
	{
		sprintf(flag_get_error(), "Invalid value for the flag '-%c`",  argv[*i][j]);
		return (1);
	}
	return 0;
}

int		flag_parse_single_flag(int argc, char **argv, int *i)
{
	int	flag_index;
	char	*equal_pos;
	int	ret;

	equal_pos = strchr(argv[*i], '=');
	if (equal_pos)
		*equal_pos = '\0';
	flag_index = _find_arg_index(argv[*i] + 2, 0);
	if (flag_index == -1)
	{
		sprintf(flag_get_error(), "The flag '%s` is invalid",  argv[*i]);
		if (equal_pos)
			*equal_pos = '=';
		return (1);
	}
	if (equal_pos)
	{
		ret = g_flags_def[flag_index].handler(argv[*i], equal_pos + 1, g_flags_def[flag_index].var);
		*equal_pos = '=';
	}
	else if ((g_flags_def[flag_index].flags & FL_IS_BOOLEAN) == 0 && argc <= *i + 1)
	{
		sprintf(flag_get_error(), "Missing value for the flag '--%s`", g_flags_def[flag_index].name);
		return (1);
	}
	else if ((g_flags_def[flag_index].flags & FL_IS_BOOLEAN) == 0)
	{
		ret = g_flags_def[flag_index].handler(argv[*i], argv[*i + 1], g_flags_def[flag_index].var);
		*i += 1;
	}
	else
		ret = g_flags_def[flag_index].handler(argv[*i], NULL, g_flags_def[flag_index].var);
	if (ret != 0)
		sprintf(flag_get_error(), "Invalid value for the flag '--%s`",  g_flags_def[flag_index].name);
	return (ret);
}

int		flag_parse(int argc, char ***av)
{
	char** const	argv = *av;
	int				i;
	int				ret;

	i = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-')
			ret = flag_parse_single_flag(argc, argv, &i);
		else if (argv[i][0] == '-')
			ret = flag_parse_multi_flag(argc, argv, &i);
		else
			break;
		if (ret != 0)
		{
			*av = &argv[i];
			return ret;
		}
		++i;
	}
	*av = &argv[i];
	return (0);
}