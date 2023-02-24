/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:06:04 by kazuki            #+#    #+#             */
/*   Updated: 2023/01/14 19:15:04 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*target;
	t_list	*next;

	if (lst == NULL || f == NULL)
		return ;
	target = lst;
	while (target->next != NULL)
	{
		next = target->next;
		f(target->content);
		target = next;
	}
	f(target->content);
}

/*
#include <stdio.h>

void	add_one(void *a)
{
	*(int *)a = *(int *)a + 1;
}

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

	ft_lstiter(lst1, add_one);
	int len;
	len = ft_lstsize(lst1);
	t_list	*itr;
	itr = lst1;
	while (len != 0)
	{
		printf("%d\n", *(int *)(itr->content));
		itr = itr->next;
		len--;
	}
	return (0);
}
*/