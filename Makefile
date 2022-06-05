# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/27 18:20:04 by ntenisha          #+#    #+#              #
#    Updated: 2022/03/27 18:26:27 by ntenisha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG =		pipex

PROG =		pipex

SRC =		pipex.c\
			utils1-libft.c\
			utils2.c\
			utils3-find_path.c\
			ft_split.c\
			ft_strjoin.c

OBJ =		$(patsubst %.c,%.o,$(SRC))

D_FILES =	$(patsubst %.c,%.d,$(SRC))

CC =		gcc

CFLAGS =	-Wall -Wextra -Werror

all: 		$(PROG)

$(PROG):	$(OBJ)
			$(CC) $(CFLAGS) $(SRC) -o $(PROG) -MD

%.o :		%.c
			$(CC) $(GFLAGS) -c $< -o $@ -MD

include		$(wildcard $(D_FILES))

clean:
			@rm -f $(OBJ) $(D_FILES)

fclean:		clean
			rm -f $(PROG)

re:			fclean all

.PHONY :	all clean fclean re