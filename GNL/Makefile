# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frogus <frogus@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/21 11:19:50 by tlorette          #+#    #+#              #
#    Updated: 2026/01/07 10:59:46 by frogus           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -L. -lft -lbsd
NAME = get_next_line.a
MAKE = make
SRCS =	get_next_line.c \
		get_next_line_utils.c \
	
OBJS = $(SRCS:.c=.o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all

test: all 
	$(MAKE) -C .. && ./a.out
.PHONY: all clean fclean re test