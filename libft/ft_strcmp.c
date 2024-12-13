/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:54:55 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/24 16:00:42 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s1a;
	unsigned char	*s2a;
	size_t			i;

	i = 0;
	s1a = (unsigned char *)s1;
	s2a = (unsigned char *)s2;
	while ((s1a[i]) || (s2a[i]))
	{
		if (s1a[i] != s2a[i])
			return (s1a[i] - s2a[i]);
		else
			i++;
	}
	return (0);
}
