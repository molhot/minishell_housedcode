/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:30:12 by satushi           #+#    #+#             */
/*   Updated: 2023/02/19 20:18:23 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief キーと値を受け取って，その組を返す.  
 * @return t_item* 
 */

t_item	*item_new(char *name, char *value)
{
	t_item	*item;

	item = malloc(sizeof(t_item));
	if (!item)
		return (NULL);
	item->name = strdup(name);
	item->value = strdup(value);
	item->next = NULL;
	return (item);
}

void	append_item(t_item **itr, t_item *item);

t_map	*map_new(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->item_head = NULL;
	return (map);
}

/**
 * @brief : map に 新しいキーと値の組みを登録する. すでに登録されているキーの時は,更新する
 * 
 * @param t_map **map 
 * @param char *name 
 * @param char *value 
 */

void	map_set(t_map **map, char *name, char *value)
{
	t_item	*itr;
	t_item	*item;

	itr = (*map)->item_head;
	while (itr != NULL)
	{
		if (strcmp(itr->name, name) == 0)
		{
			free(itr->value);
			itr->value = strdup(value);
			return ;
		}
		itr = itr->next;
	}
	item = item_new(name, value);
	append_item(&(*map)->item_head, item);
}

/**
 * @brief map に登録されている item を削除する
 * 
 * @param t_map **map 
 * @param char *name 
 */

void	map_unset(t_map **map, char *name)
{
	t_item	*prev;
	t_item	*itr;

	prev = (*map)->item_head;
	itr = prev->next;
	if (strcmp(prev->name, name) == 0)
	{
		free(prev->name);
		free(prev->value);
		free(prev);
		(*map)->item_head = itr;
	}
	while (itr)
	{
		if (strcmp(itr->name, name) == 0)
		{
			free(itr->name);
			free(itr->value);
			prev->next = itr->next;
			free(itr);
			return ;
		}
		prev = itr;
		itr = itr->next;
	}
}

char	*map_get(t_map *map, const char *name)
{
	t_item	*itr;

	itr = map->item_head;
	while (itr != NULL)
	{
		if (strcmp(itr->name, name) == 0)
			return (itr->value);
		itr = itr->next;
	}
	return (NULL);
}

void	append_item(t_item **target, t_item *item)
{
	if ((*target) == NULL)
	{
		(*target) = item;
		return ;
	}
	append_item(&(*target)->next, item);
}

#ifdef TEST

// #include <assert.h>
// void	test_item(void)
// {
// 	t_item *target = item_new("hoge", "huga");

// 	t_item *item2 = item_new("hello", "world");
// 	append_item(&target, item2);
// 	assert(strcmp(target->name, "hoge") == 0);
// 	assert(strcmp(target->next->name, "hello") == 0);

// 	t_item *item3 = item_new("FOO", "BAR");
// 	append_item(&target, item3);
// 	assert(strcmp(target->next->next->name, "FOO") == 0);
// 	printf("%s\n", target->next->next->name);
// }

// int main(void)
// {
//     t_item  *item = item_new("hoge", "huga");
//     assert(strcmp(item->name, "hoge") == 0);
//     assert(strcmp(item->value, "huga") == 0);
//     t_map *map = map_new();
//     assert(map->item_head == NULL);
//     map_set(&map, "hoge", "huga");
//     assert(strcmp(map->item_head->name, "hoge") == 0);
//     map_set(&map, "hello", "world");
//     assert(strcmp(map->item_head->name, "hoge") == 0);
//     assert(strcmp(map->item_head->next->name, "hello") == 0);

//     map_set(&map, "hoge", "HELLO");
//     char *value = map_get(map, "hoge");
//     assert(strcmp(value, "HELLO") == 0);

//     /* map_get */
//     value = map_get(map, "hello");
//     assert(strcmp(value, "world") == 0);

//     t_item *itr = map->item_head;
//     /*while (itr)
//     {
//         printf("%s\n", itr->name);
//         itr = itr->next;
//     }*/

//     /* map_unset */
//     map_set(&map, "FOO", "BAR");
//     map_unset(&map, "hello");
//     value = map_get(map, "hello");
//     // printf("%s\n", value);
//     assert(value == NULL);
//     assert(strcmp(map->item_head->name, "hoge") == 0);
//     assert(strcmp(map->item_head->next->name, "FOO") == 0);
//     // printf("%s\n", map->item_head->next->name);

//     // 先頭をunset
//     map_unset(&map, "hoge");

//     /*itr = map->item_head;
//     while (itr)
//     {
//         printf("%s\n", itr->name);
//         itr = itr->next;
//     }*/
// }
#endif
