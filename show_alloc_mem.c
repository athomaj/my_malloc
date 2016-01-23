/*
** show_alloc_mem.c for  in /home/maillo_a/rendu/PSU_2014_malloc
** 
** Made by Flavien Maillot
** Login   <maillo_a@epitech.net>
** 
** Started on  Sun Feb 15 15:34:36 2015 Flavien Maillot
** Last update Sun Feb 15 22:11:12 2015 julien athomas
*/

#include	"header.h"

void		show_alloc_mem()
{
  t_block	*block;

  block = g_first_block;
  if (block == NULL || block->prev == NULL)
    return ;
  printf("break : %p\n", block->prev + sizeof(t_block) + block->prev->size);
  while (block)
    {
      if (block->is_free == 0)
	{
	  printf("%p - %p : %d octects\n", (void *)(block->data),
		 (void *)((block->data) + block->size),
		 (int)((void *)((block->data) + block->size) -
		       (void *)(block->data)));
	}
      block = block->next;
    }
}
