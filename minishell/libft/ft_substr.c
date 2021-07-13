/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:32:35 by yait-kad          #+#    #+#             */
/*   Updated: 2019/11/15 17:34:55 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	unsigned int	i;
	size_t			j;

	if (!s)
		return (NULL);
	j = ft_strlen(s);
	if (j < start)
		return (ft_strdup("\0"));
	if (len >= j)
		if (!(dest = (char *)malloc(sizeof(char) * ((j - start) + 1))))
			return (NULL);
	if (len < j)
		if (!(dest = (char *)malloc(sizeof(char) * (len + 1))))
			return (NULL);
	i = start;
	j = 0;
	while (s[i] != '\0' && j < len)
	{
		dest[j] = s[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}
