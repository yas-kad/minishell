/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 15:15:59 by yait-kad          #+#    #+#             */
/*   Updated: 2019/11/11 19:18:12 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*data_memory;

	data_memory = malloc(count * size);
	if (!data_memory)
		return (NULL);
	data_memory = ft_memset(data_memory, 0, size * count);
	return (data_memory);
}
