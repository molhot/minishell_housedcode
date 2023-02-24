/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:51:00 by kazuki            #+#    #+#             */
/*   Updated: 2023/01/14 19:03:40 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*target;
	t_list	*next;

	if (lst == NULL || del == NULL || *lst == NULL)
		return ;
	target = *lst;
	while (target->next != NULL)
	{
		next = target->next;
		ft_lstdelone(target, del);
		target = next;
	}
	ft_lstdelone(target, del);
}

/*__attribute__((destructor))
static void destructor() {
    system("leaks -q a.out");
}

#include <stdio.h>
int main(void)
{
	int	*data1 = (int *)malloc(sizeof(int)); 
	int *data2 = (int *)malloc(sizeof(int)); 
	int *data3 = (int *)malloc(sizeof(int)); 
	int	*data4 = (int *)malloc(sizeof(int));  
	int *data5 = (int *)malloc(sizeof(int)); 
	

	*data1 = 1;
	*data2 = 2;
	*data3 = 3;
	*data4 = 4;
	*data5 = 5;

	t_list *lst1 = ft_lstnew(data1);
	t_list *lst2 = ft_lstnew(data2);
	t_list *lst3 = ft_lstnew(data3);
	t_list *lst4 = ft_lstnew(data4);
	t_list *lst5 = ft_lstnew(data5);

	ft_lstadd_front(&lst2, lst1);
	ft_lstadd_front(&lst3, lst2);
	ft_lstadd_front(&lst4, lst3);
	ft_lstadd_front(&lst5, lst4);

	int res = ft_lstsize(lst1);
	printf("%d\n", res);

	ft_lstclear(&lst1, free);
	return (0);
}
*/
