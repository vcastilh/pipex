# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcastilh <vcastilh@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 00:26:46 by vcastilh          #+#    #+#              #
#    Updated: 2022/04/22 00:26:48 by vcastilh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -c
SRCS = main.c
LIBFT = libft.a
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -Llibft -lft -o $(NAME)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -Ilibft

$(LIBFT):
	make -C libft

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all