/*
** calloc.c for  in /home/maillo_a/rendu/PSU_2014_malloc
** 
** Made by Flavien Maillot
** Login   <maillo_a@epitech.net>
** 
** Started on  Sun Feb 15 16:07:04 2015 Flavien Maillot
** Last update Sun Feb 15 21:57:41 2015 julien athomas
*/

#include	"header.h"

void		*calloc(size_t nb_size, size_t size)
{
  void		*new_ptr;

  if ((new_ptr = malloc(nb_size * size)) == NULL)
    return (NULL);
  memset(new_ptr, 0, nb_size * size);
  return (new_ptr);
}

void		*split_page(t_block *old_block, size_t size)
{
  t_block	*new_block;

  new_block = (void *)(old_block) + sizeof(t_block) + old_block->size;
  new_block->size = size - sizeof(t_block);
  new_block->next = NULL;
  new_block->prev = old_block;
  new_block->magic = MAGIC_NB;
  new_block->is_free = 1;
  if (g_first_block)
    g_first_block->prev = new_block;
  return (new_block);
}

void		*split_block(t_block *old_block, size_t size)
{
  t_block	*new_block;

  new_block = (void *)(old_block) + sizeof(t_block) + size;
  new_block->size = old_block->size - size - sizeof(t_block);
  new_block->next = old_block->next;
  if (new_block->next == NULL)
    g_first_block->prev = new_block;
  else
    new_block->next->prev = new_block;
  new_block->prev = old_block;
  new_block->magic = MAGIC_NB;
  new_block->is_free = 1;
  return (new_block);
}
