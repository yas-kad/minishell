/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 11:42:53 by yait-kad          #+#    #+#             */
/*   Updated: 2019/11/15 16:39:16 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *c1, int c2)
{
	int		index;
	size_t	len;

	index = 0;
	len = ft_strlen(c1);
	if ((char)c2 == '\0')
		return ((char *)c1 + len);
	while (c1[index] != '\0')
	{
		if (c2 == c1[index])
			return ((char *)c1 + index);
		index++;
	}
	return (NULL);
}
