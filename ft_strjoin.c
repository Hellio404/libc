/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:58:39 by yfarini           #+#    #+#             */
/*   Updated: 2022/08/25 13:59:13 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char *strjoin(const char *s1, const char* s2)
{
    size_t  s1_size;
    char    *str;

    if (s1 == NULL) 
        s1 = "";
    if (s2 == NULL)
        s2 = "";

    s1_size = strlen(s1);
    str = malloc((s1_size + strlen(s2) + 1));
    if (str == NULL)
        return (NULL);
    strcpy(str, s1);
    strcpy(str + s1_size, s2);
    return (str);
}
