/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:41:28 by kazuki            #+#    #+#             */
/*   Updated: 2023/01/14 19:04:35 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
}

/*
__attribute__((destructor))
static void destructor() {
    system("leaks -q a.out");
}

#include <assert.h>
#include <stdio.h>
int main(void)
{
	int		*data1;
	int		*data2;
	t_list	*after;
	t_list	*before;

	data1 = (int*)malloc(sizeof(int));
	data2 = (int*)malloc(sizeof(int));
	*data1 = 1;
	*data2 = 2;
	before = ft_lstnew(data1);
	after = ft_lstnew(data2);
	
	ft_lstadd_back(&before, after);
	assert(before->next->content == data2);
	ft_lstdelone(before, free);
	assert(after->content == data2);
}
*/