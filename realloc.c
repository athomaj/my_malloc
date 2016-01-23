/*
** realloc.c for  in /home/athoma_j/rendu/PSU_2014_malloc
** 
** Made by julien athomas
** Login   <athoma_j@epitech.net>
** 
** Started on  Tue Feb  3 13:22:43 2015 julien athomas
** Last update Sun Feb 15 23:39:52 2015 Flavien Maillot
*/

#include	"header.h"

void		*realloc(void *ptr, size_t size)
{
  void		*new_ptr;

  size = allign(size);
  if (size == 0 && ptr != NULL)
    {
      free(ptr);
      return (NULL);
    }
  if (pthread_mutex_lock(&g_lock) != 0)
    fprintf(stderr, "Mutex lock Failed");
  if (pthread_mutex_unlock(&g_lock) != 0)
    fprintf(stderr, "Mutex lock Failed");
  if ((new_ptr = malloc(size)) == NULL)
    return (NULL);
  if (ptr == NULL)
    return (new_ptr);
  new_ptr = memmove(new_ptr, ptr, size);
  free(ptr);
  return (new_ptr);
}
