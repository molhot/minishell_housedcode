/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:01:39 by kazuki            #+#    #+#             */
/*   Updated: 2023/01/14 18:12:22 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL || *lst == NULL)
		return ;
	new->next = *lst;
}

/*#include <assert.h>
#include <stdio.h>
int main(void)
{
	int		data1;
	int		data2;
	t_list	*new;
	t_list	*before;

	data1 = 10;
	data2 = -10;
	before = ft_lstnew(&data1);
	new = ft_lstnew(&data2);
	
	ft_lstadd_front(&before, new);
	// printf("%d\n", *((int *)new->content));
	// assert(lst->content == &data1);
	printf("%d\n", *((int *)new->next->content));
	assert(new->next->content == &data1);
}*/
