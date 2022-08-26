/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:31:38 by yfarini           #+#    #+#             */
/*   Updated: 2022/08/26 15:40:05 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "vector.h"

t_vector	*v_create(size_t size)
{
	t_vector	*ptr;

	ptr = malloc(sizeof(t_vector));
	if (!ptr)
		return (NULL);
	ptr->_end = NULL;
	ptr->_begin = NULL;
	ptr->_end_cap = NULL;
	ptr->_size = size;
	return (ptr);
}

void	*v_push(t_vector *vt)
{
	size_t	new_size;
	void	*ret;

	if (vt->_end + vt->_size > vt->_end_cap)
	{
		new_size = (((unsigned char *)vt->_end
					- (unsigned char *)vt->_begin) / vt->_size) * 2;
		if (new_size == 0)
			new_size = 1;
		if (v_reserve(vt, new_size))
			return (NULL);
	}
	ret = vt->_end;
	vt->_end += vt->_size;
	return (ret);
}

void	v_pop(t_vector *vt, void (*fn)(void *))
{
	if (vt->_end <= vt->_begin)
		return ;
	vt->_end -= vt->_size;
	if (fn)
		fn(vt->_end);
	
	
}

int	v_reserve(t_vector *vt, size_t size)
{
	size_t	new_size;
	void	*replace;

	if (v_capacity(vt) >= size)
		return (0);
	new_size = size * vt->_size;
	if (new_size == 0)
		new_size = 1;
	replace = malloc(new_size * vt->_size);
	if (!replace)
		return (1);
	memcpy(replace, vt->_begin,
		((unsigned char *)vt->_end - (unsigned char *)vt->_begin));
	free(vt->_begin);
	vt->_end_cap = replace + new_size * vt->_size;
	vt->_end = replace + ((unsigned char *)vt->_end
			- (unsigned char *)vt->_begin);
	vt->_begin = replace;
	return (0);
}

int	v_resize(
	t_vector *vt,
	size_t size,
	const void *default_value,
	void (*fn) (void *))
{
	size_t	diff;
	size_t	i;

	while (v_size(vt) > size)
		v_pop(vt, fn);
	if (v_size(vt) < size)
	{
		if (v_reserve(vt, size))
			return (1);
		diff = size - v_size(vt);
		while (i < diff)
		{
			memmove(vt->_end, default_value, vt->_size);
			vt->_end += vt->_size;
			++i;
		}
	}
	return (0);
}

size_t	v_size(t_vector *vt)
{
	return (
		((unsigned char*)vt->_end - (unsigned char *)vt->_begin)
		/ vt->_size
	);
}

size_t	v_capacity(t_vector *vt)
{
	return (
		((unsigned char*)vt->_end_cap - (unsigned char *)vt->_begin)
		/ vt->_size
	);
}

int	v_empty(t_vector *vt)
{
	return (v_size(vt) == 0);
}

void	*v_begin(t_vector *vt)
{
	return (vt->_begin);
}

void	*v_end(t_vector *vt)
{
	return (vt->_end);
}

void	*v_get(t_vector *vt, size_t index)
{
	return (v_begin(vt) + vt->_size * index);
}

void	v_clear(t_vector *vt, void (*fn) (void *))
{
	void	*begin;

	if (fn)
	{
		begin = vt->_begin;
		while (begin != vt->_end)
		{
			fn(begin);
			begin += vt->_size;
		}
	}
	free(vt->_begin);
	vt->_begin = NULL;
	vt->_end = NULL;
	vt->_end_cap = NULL;
}

void	v_destroy(t_vector *vt, void (*fn) (void *))
{
	if (!vt)
		return ;
	v_clear(vt, fn);
	free(vt);
}
