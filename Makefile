# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcastilh <vcastilh@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 00:26:46 by vcastilh          #+#    #+#              #
#    Updated: 2022/05/24 16:08:51 by coder            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -c
LIBFT = libft.a
SRCS = main.c \
	   get_data.c \
	   child.c \
	   handle_exit.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -Llibft -lft -o $(NAME) 

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -Ilibft $(SRCS) 

$(LIBFT):
	make -C libft

clean:
	rm -rf $(OBJS) 

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
