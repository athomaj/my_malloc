/*
** malloc.c for  in /home/athoma_j/rendu/new_malloc
** 
** Made by julien athomas
** Login   <athoma_j@epitech.net>
** 
** Started on  Tue Feb 10 19:51:25 2015 julien athomas
** Last update Sun Feb 15 22:26:11 2015 Flavien Maillot
*/

#include	"header.h"

t_block		*g_first_block = NULL;
pthread_mutex_t	g_lock = PTHREAD_MUTEX_INITIALIZER;

void		*create_new_page(t_block *old_block, size_t size)
{
  size_t	pow_size;
  t_block	*new_block;
  size_t	page_size;

  page_size = (size_t)getpagesize();
  size = size + sizeof(t_block);
  pow_size = size / page_size;
  pow_size += (size % page_size == 0 ? 0 : 1);
  if ((new_block = sbrk(page_size * pow_size)) == (void *)-1)
    return (NULL);
  new_block->size = size - sizeof(t_block);
  new_block->next = NULL;
  new_block->prev = old_block;
  new_block->magic = MAGIC_NB;
  new_block->is_free = 0;
  if (g_first_block)
    g_first_block->prev = new_block;
  if (page_size * pow_size - size >= sizeof(t_block) + 8)
    new_block->next = split_page(new_block,
  				 page_size * pow_size - size);
  return (new_block);
}

void		*unlock_mutex()
{
  if (pthread_mutex_unlock(&g_lock) != 0)
    fprintf(stderr, "Mutex lock Failed");
  return (NULL);
}

void		*check_with_last_free(t_block *previous, size_t size)
{
  previous->next = create_new_page(previous, size - previous->size +
				   sizeof(t_block));
  previous->size += previous->next->size + sizeof(t_block);
  previous->is_free = 0;
  if (previous->next)
    previous->next = previous->next->next;
  if (previous->next)
    previous->next->prev = previous;
  if (g_first_block)
    g_first_block->prev = (previous->next == NULL ? previous :
			   previous->next);
  return (previous);
}

void		*check_pages(size_t size)
{
  t_block	*tmp;
  t_block	*previous;

  tmp = g_first_block;
  while (tmp && !(tmp->is_free != 0 && tmp->size >= size))
    {
      previous = tmp;
      tmp = tmp->next;
    }
  if (!tmp)
    {
      if (previous->is_free == 1)
	return (check_with_last_free(previous, size));
      else
	previous->next = create_new_page(previous, size);
      return (previous->next);
    }
  tmp->is_free = 0;
  if (tmp->size > size && ((tmp->size - size) >= sizeof(t_block) + 8))
    {
      tmp->next = split_block(tmp, size);
      tmp->size = size;
    }
  return (tmp);
}

void		*malloc(size_t size)
{
  t_block	*new_block;

  if (size <= 0)
    return (NULL);
  if (pthread_mutex_lock(&g_lock) != 0)
    fprintf(stderr, "Mutex lock Failed");
  size = allign(size);
  if (g_first_block == NULL)
    {
      if ((new_block = create_new_page(NULL, size)) == NULL)
	return (unlock_mutex());
      new_block->prev = new_block;
      g_first_block = new_block;
    }
  else if ((new_block = check_pages(size)) == NULL)
    return (unlock_mutex());
  if (pthread_mutex_unlock(&g_lock) != 0)
    fprintf(stderr, "Mutex lock Failed");
  return (new_block->data);
}
