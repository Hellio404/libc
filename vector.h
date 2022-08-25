/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:47:36 by yfarini           #+#    #+#             */
/*   Updated: 2022/08/25 10:14:52 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <string.h>

typedef struct s_vector
{
	void	*_end_cap;
	void	*_end;
	size_t	_size;
	void	*_begin;
}				t_vector;

/**
 * @brief create a vector with 0 elements of size 'size'
 * 
 * @param size the size of the type that will be inserted to the vector
 * @return t_vector* the vector pointer (NULL in case of failure)
 */
t_vector	*v_create(size_t size);

/**
 * @brief push the end of the vector by one and return a pointer to the old end
 * 
 * @param vt the vector pointer
 * @return void* pointer to the element before the end
 */
void		*v_push(t_vector *vt);

/**
 * @brief remove an element from the end of the vector
 * 
 * @param vt the vector pointer
 * @param fn a function to run on the last element before removing it (eg: free)
 */
void		v_pop(t_vector *vt, void (*fn) (void *));

/**
 * @brief reserve the capacity size on the vector.
 * On success is guaranteed that the capacity of the vector will be >= size
 * 
 * @param vt the vector pointer
 * @param size the capacity to reserve
 * @return int 
 */
int			v_reserve(t_vector *vt, size_t size);

/**
 * 
 * @brief resize the vector to be exactly "size" if the vector has more
 * elements than "size" all the additional elements will be removed
 * form the end of the vector. If the vector has less elements than "size",
 * values will be added to the end of the vector using the "default_value"
 * 
 * @param vt the vector pointer
 * @param size the target size of the vector
 * @param default_value a pointer to the default value used to
 * 						fill the needed elements
 * @param fn a function that will be called before the any element destruction
 * 			OR NULL if no action needed
 * @return int 0 on success and 1 otherwise
 */
int			v_resize(
				t_vector *vt,
				size_t size,
				const void *default_value,
				void (*fn) (void *)
				);

/**
 * @brief return the current size of the vector
 * 
 * @param vt the vector pointer
 * @return size_t the size of the vector
 */
size_t		v_size(t_vector *vt);

/**
 * @brief return the current capacity of the vector
 * 
 * @param vt the vector pointer
 * @return size_t the capacity of the vector
 */
size_t		v_capacity(t_vector *vt);

/**
 * @brief return whather the vector is empty
 * 	or not (1 if it's empty and 0 if it's not)
 * 
 * @param vt the vector pointer
 * @return int 1 if the vector is empty and 0 if it's not
 */
int			v_empty(t_vector *vt);

/**
 * @brief return a pointer to the beginning of the data hold by the vector
 * 
 * @param vt the vector pointer
 * @return void* the beginning
 */
void		*v_begin(t_vector *vt);

/**
 * @brief return a pointer to the past the end of the data hold by the vector
 * 
 * @param vt the vector pointer
 * @return void* the end of the vector
 */
void		*v_end(t_vector *vt);

/**
 * @brief return a pointer to the n-th element in the vector
 * 
 * @param vt the vector pointer
 * @param index the possition of the element to get
 * @return void* the end of the vector
 */
void	*v_get(t_vector *vt, size_t index);

/**
 * @brief remove all the elements on vector
 * 
 * @param vt the vector pointer
 * @param fn a function to run before removing each element.
 * 			it can be NULL if no action needed
 */
void		v_clear(t_vector *vt, void (*fn) (void *));

/**
 * @brief remove and free all the resources allocated by the vector
 * 
 * @param vt the vector pointer
 * @param fn a function to run before removing each element.
 * 			it can be NULL if no action needed
 */
void		v_destroy(t_vector *vt, void (*fn) (void *));
#endif
