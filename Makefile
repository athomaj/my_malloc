##
## Makefile for  in /home/athoma_j/rendu/PSU_2014_malloc
##
## Made by julien athomas
## Login   <athoma_j@epitech.net>
##
## Started on  Mon Feb  2 21:35:53 2015 julien athomas
## Last update Sun Feb 15 23:17:47 2015 julien athomas
##

SRC=		malloc.c		\
		free.c			\
		realloc.c		\
		show_alloc_mem.c	\
		calloc.c		\

NAME=		libmy_malloc_$(HOSTTYPE).so

LINKNAME=	libmy_malloc.so

OBJ=		$(SRC:.c=.o)


all:		$(NAME)

$(NAME):	$(OBJ)
		gcc -o $(NAME) -shared $(OBJ)
		ln -f $(NAME) $(LINKNAME)
clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME) $(LINKNAME)

re:		fclean all

.PHONY:		all clean flcean re
