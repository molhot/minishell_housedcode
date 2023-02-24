/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:12:52 by kazuki            #+#    #+#             */
/*   Updated: 2023/01/14 18:27:10 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*itr;

	size = 0;
	itr = lst;
	if (itr == NULL)
		return (-1);
	while (itr != NULL)
	{
		size++;
		if (size == INT_MAX)
			return (INT_MAX);
		itr = itr->next;
	}
	return (size);
}

/*#include <stdio.h>
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

}
*/
