#include <stdio.h>
#include <stdlib.h>

#define __debug__

enum cell_state {
	empty,
	used,
	dirtied, /* unused */
};

struct cell {
	int blocknum;
	enum cell_state state;

	struct cell *prev;
	struct cell *next;
};

struct list {
	int length;
	struct cell *cell_list;
	struct cell head;
};

struct cell *alloc_cell(int blocknum)
{
	struct cell *tmp;

	tmp = (struct cell *)malloc(sizeof(struct cell));
	if (tmp == NULL) goto end;

	tmp->blocknum = blocknum;
	tmp->state    = empty;
	tmp->prev     = NULL;
	tmp->next     = NULL;

end:
	return tmp;
}

struct list *alloc_list(int length)
{
	int         i;
	struct list *tmp_list;
	struct cell *tmp_cell;

	tmp_list = (struct list*)malloc(sizeof(struct list));
	if (tmp_list == NULL) goto error;

	tmp_list->length    = length;
	tmp_list->head.prev = &tmp_list->head;
	tmp_list->head.next = &tmp_list->head;

	/* create/initialize cell list */
	for (i = 0; i < length; i++) {
		tmp_cell = alloc_cell(-1);
		if (tmp_cell == NULL) goto error;

		tmp_cell->prev            = &tmp_list->head;
		tmp_cell->next            = tmp_list->head.next;
		tmp_list->head.next->prev = tmp_cell;
		tmp_list->head.next       = tmp_cell;
	}

	return tmp_list;

error:
	return NULL;
}

/*
 * cache_hit_fifo()
 *
 * does nothing needed.
 */

void cache_hit_fifo(struct cell *target, struct list *list)
{
	struct cell *last;
	for(last = list->head.prev; last != &list->head && last->state == empty; last = last->prev) 
	
	target->prev->next = target->next;
	target->next->prev = target->prev;

	target->prev             = last;
	target->next             = last->next;
	last->next->prev         = target;
	last->next               = target;
	
	return ;
}

/*
 * cache_miss_fifo()
 *
 * If target is free, put blocknum in the target.
 * Otherwise, reclaim the cell from the head of the cell list, 
 * and move the end cell to the list end.
 */

void cache_miss_fifo(int blocknum, struct cell *target, struct list *list)
{
	struct cell *tmp;

	if (target != &list->head && target->state == empty) {
		target->blocknum = blocknum;
		target->state    = used;
	} else {
		tmp             = list->head.next;
		tmp->blocknum   = blocknum;

		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;

		tmp->prev             = list->head.prev;
		tmp->next             = &list->head;
		list->head.prev->next = tmp;
		list->head.prev       = tmp;
	}

	return ;
}

void block_access(int blocknum, struct list *list)
{
	struct cell *tmp, *head;
	
	for (tmp = list->head.next; tmp != &list->head; tmp = tmp->next) {
		if (tmp->blocknum == blocknum || tmp->state == empty) break;
	}
	
	if (tmp != &list->head && tmp->state == used)
		cache_hit_fifo(tmp, list); /* cache is hit */
	else
		cache_miss_fifo(blocknum, tmp, list); /* cache is NOT hit... */
	
	return ;
}

void __debug__ show_list(struct list *list)
{
	struct cell *tmp;
	
	for (tmp = list->head.next; tmp != &list->head; tmp = tmp->next) {
		if (tmp == NULL) break;
		if (tmp->state == used) printf("(%d)->", tmp->blocknum);
	}
	printf("(end)\n");
	return ;
}

int main()
{
	struct list *my_list;
	
	my_list = alloc_list(3);

	block_access(4, my_list);
	block_access(2, my_list);
	block_access(4, my_list);
	block_access(3, my_list);
	block_access(4, my_list);
	block_access(5, my_list);
	block_access(3, my_list);
	block_access(1, my_list);
	block_access(6, my_list);

	show_list(my_list);

	return 0;
}
