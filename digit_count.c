/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:44:14 by yfarini           #+#    #+#             */
/*   Updated: 2022/08/26 10:44:36 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	digit_count(size_t n)
{
	size_t	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n)
	{
		++count;
		n /= 10;
	}
	return (count);
}
