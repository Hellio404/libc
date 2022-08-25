/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:05:00 by yfarini           #+#    #+#             */
/*   Updated: 2022/08/25 11:09:36 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

static size_t	partition(
	t_vector *array,
	ssize_t start,
	ssize_t end,
	t_comparator comp,
	t_swapper swap)
{
	void		*pivot;
	ssize_t		left;
	ssize_t		right;

	pivot = v_get(array, end);
	left = start;
	right = start;
	while (right < end)
	{
		if (comp(v_get(array, right), pivot) <= 0)
		{
			swap(v_get(array, right), v_get(array, left));
			++left;
		}
		++right;
	}
	swap(v_get(array, left), pivot);
	return (left);
}

static void	quick_sort(
	t_vector *array,
	ssize_t start,
	ssize_t end,
	t_comparator comp,
	t_swapper swap)
{
	size_t	pivot_index;

	if (start >= end)
		return ;
	pivot_index = partition(array, start, end, comp, swap);
	quick_sort(array, start, pivot_index - 1, comp, swap);
	quick_sort(array, pivot_index + 1, end, comp, swap);
}

void	sort(t_vector *array, t_comparator comp, t_swapper swap)
{
	if (v_size(array) <= 1)
		return ;
	quick_sort(array, 0, v_size(array) - 1, comp, swap);
}
