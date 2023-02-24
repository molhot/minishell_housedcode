/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:17:30 by kazuki            #+#    #+#             */
/*   Updated: 2023/01/14 20:0 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*target;
	t_list	*next;
	int		size;
	int		i;

	i = 0;
	if (lst == NULL || f == NULL)
		return (NULL);
	ret = (t_list *)malloc(sizeof(t_list));
	if (ret == NULL)
		return (NULL);
	ret = ft_lstnew(f(lst->content));
	target = lst->next;
	size = ft_lstsize(lst) - 1;
	while (i < size)
	{
		next = target->next;
		ft_lstadd_back(&ret, ft_lstnew(f(target->content)));
		target = next;
		i++;
	}
	if (del != NULL)
		ft_lstclear(&lst, del);
	return (ret);
}

/*#include <stdio.h>
void	*add_one(void *a)
{
	int *res = (int *)malloc(sizeof(int));
	*res = *(int*)a + 1;
	return (res);
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

     t_list *res;

    	res = ft_lstmap(lst1, add_one, NULL);
    	int len;
	len = ft_lstsize(res);
	//printf("%d\n", len);
	//printf("%d\n", *((int *)res->content));
	//printf("%d\n", *((int *)res->next->content));
	t_list	*itr;
	itr = res;
	for (int i = 0; i < len; i++)
	{
		printf("%d\n", *(int *)(itr->content));
		itr = itr->next;
	}
	return (0);
}
*/