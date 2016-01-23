/*
** header.h for  in /home/athoma_j/rendu/tpMalloc
** 
** Made by julien athomas
** Login   <athoma_j@epitech.net>
** 
** Started on  Thu Jan 29 18:24:04 2015 julien athomas
** Last update Sun Feb 15 22:23:20 2015 Flavien Maillot
*/

#ifndef MALLOC_H_
# define MALLOC_H_

# include		<stdlib.h>
# include		<stdio.h>
# include		<unistd.h>
# include		<errno.h>
# include		<string.h>
# include		<pthread.h>

# define		HEADER_SIZE 29
# define		MAGIC_NB 83223
# define		allign(x) (((((x) - 1) / 8) * 8) + 8)

typedef struct		s_block
{
  size_t		size;
  struct s_block	*next;
  struct s_block	*prev;
  int			magic;
  char			is_free;
  char			data[1];
}			t_block;

void			free(void *);
void			*malloc(size_t);
void			display_mem();

void			show_alloc_mem();

void			*calloc(size_t nb_size, size_t size);
void			*split_page(t_block *old_block, size_t size);
void			*split_block(t_block *old_block, size_t size);

extern t_block		*g_first_block;
extern pthread_mutex_t	g_lock;

#endif /* !MALLOC_H_ */
