/*
** free.c for  in /home/athoma_j/rendu/new_malloc
** 
** Made by julien athomas
** Login   <athoma_j@epitech.net>
** 
** Started on  Tue Feb 10 21:40:05 2015 julien athomas
** Last update Sun Feb 15 22:17:49 2015 julien athomas
*/

#include	"header.h"

void		merge_block(t_block *old_block)
{
  old_block->size += old_block->next->size + sizeof(t_block);
  old_block->next = old_block->next->next;
  if (old_block->next)
    old_block->next->prev = old_block;
  else if (g_first_block)
    g_first_block->prev = old_block;
  old_block->is_free = 1;
}

void		check_block(t_block *block)
{
  t_block	*to_free;
  size_t	size;
  size_t	page_size;

  page_size = (size_t)getpagesize();
  to_free = block;
  if (block->next && block->next->is_free == 1)
    merge_block(block);
  if (block && block != g_first_block && block->prev &&
      block->prev->is_free == 1)
    {
      merge_block(block->prev);
      to_free = block->prev;
    }
  if (to_free->next == NULL)
    {
      if (to_free->size > page_size)
	{
	  size = to_free->size % page_size;
	  brk((void *)to_free + size + sizeof(t_block));
	  to_free->size = size;
	}
    }
}

void		free(void *ptr)
{
  t_block	*head;

  if (ptr == NULL)
    return ;
  head = ptr - HEADER_SIZE;
  if (head < g_first_block || head > g_first_block->prev ||
      head->magic != MAGIC_NB || head->is_free == 1)
    {
      fprintf(stderr, "Memory corruption\n");
      abort();
      return ;
    }
  if (pthread_mutex_lock(&g_lock) != 0)
    fprintf(stderr, "Mutex lock Failed");
  head->is_free = 1;
  check_block(head);
  if (pthread_mutex_unlock(&g_lock) != 0)
    fprintf(stderr, "Mutex lock Failed");
}
