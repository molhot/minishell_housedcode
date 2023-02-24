/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:33:10 by kazuki            #+#    #+#             */
/*   Updated: 2023/01/14 18:39:10 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL || new == NULL || *lst == NULL)
		return ;
	last = ft_lstlast(*lst);
	last->next = new;
}

/*#include <assert.h>
#include <stdio.h>
int main(void)
{
	int		data1;
	int		data2;
	t_list	*after;
	t_list	*before;

	data1 = 1;
	data2 = 2;
	before = ft_lstnew(&data1);
	after = ft_lstnew(&data2);
	
	ft_lstadd_back(&before, after);
	// printf("%d\n", *((int *)->content));
	// assert(lst->content == &data1);
	printf("%d\n", *((int *)before->next->content));
	assert(before->next->content == &data2);
}
*/