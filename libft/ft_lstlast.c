/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:24:19 by kazuki            #+#    #+#             */
/*   Updated: 2023/01/14 18:50:13 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int		len;
	t_list	*last;

	if (lst == NULL)
		return (NULL);
	len = ft_lstsize(lst);
	last = lst;
	while (len != 1)
	{
		last = last->next;
		len--;
	}
	return (last);
}

/*#include <stdio.h>
#include <assert.h>
int main(void)
{
	int	data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int	data4 = 4;
	int data5 = 5;

	t_list *lst1 = ft_lstnew(&data1);
	t_list *lst2 = ft_lstnew(&data2);
	t_list *lst3 = ft_lstnew(&data3);
	t_list *lst4 = ft_lstnew(&data4);
	t_list *lst5 = ft_lstnew(&data5);

	ft_lstadd_front(&lst2, lst1);
	ft_lstadd_front(&lst3, lst2);
	ft_lstadd_front(&lst4, lst3);
	ft_lstadd_front(&lst5, lst4);

	int res = ft_lstsize(lst1);
	printf("%d\n", res);
	
	t_list *last = ft_lstlast(lst1);
	// printf("%d\n", *((int *)last->content));
	assert(last == lst5);
}
*/