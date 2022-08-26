/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:08:11 by yfarini           #+#    #+#             */
/*   Updated: 2022/08/25 11:30:11 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

# include <stdint.h>
# include "vector.h"

typedef int8_t	(*t_comparator)(void *, void *);
typedef void	(*t_swapper)(void *, void *);

void	sort(t_vector *array, t_comparator comp, t_swapper swap);

#endif
