/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:52:05 by yait-kad          #+#    #+#             */
/*   Updated: 2019/11/11 19:21:37 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	len_dest;

	k = 0;
	j = ft_strlen(src);
	if (!dest && size == 0)
		return (j);
	i = ft_strlen(dest);
	len_dest = i;
	if (i >= size)
		return (j + size);
	while (src[k] && i < size - 1)
	{
		dest[i++] = src[k];
		k++;
	}
	dest[i] = '\0';
	return (len_dest + j);
}
