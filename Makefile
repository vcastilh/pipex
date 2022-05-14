# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcastilh <vcastilh@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 00:26:46 by vcastilh          #+#    #+#              #
#    Updated: 2022/05/14 02:22:11 by coder            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -c
LIBFT = libft.a
SRCS = main.c \
	   get_data.c \
	   child.c \

all: $(NAME)

$(NAME): $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) -Ilibft
	$(CC) *.o -Llibft -lft -o $(NAME) 
	# remove wildcards later


$(LIBFT):
	make -C libft

clean:
	rm -rf *.o 

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all
