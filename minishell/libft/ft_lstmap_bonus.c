/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:18:45 by yait-kad          #+#    #+#             */
/*   Updated: 2019/11/14 14:45:04 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*l;

	l = (t_list *)malloc(sizeof(t_list));
	while (l)
	{
		l = (*f)(lst->content);
		lst = lst->next;
		l = l->next;
		(*del)(l->next);
	}
	return (l);
}
