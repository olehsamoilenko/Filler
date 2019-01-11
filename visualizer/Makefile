# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osamoile <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/01 15:53:40 by osamoile          #+#    #+#              #
#    Updated: 2018/11/12 16:23:19 by osamoile         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			visualizer
INC =			-I ../libft/includes #-I ./includes
				
LIB =			-lncurses -lft -L ../libft
FLAGS =			#-Wall -Wextra -Werror
LIST =			visual
OBJ =			$(addprefix obj/, $(addsuffix .o, $(LIST)))

all: $(NAME)

obj/%.o: src/%.c
	gcc $(FLAGS) -c $< -o $@ $(INC)

$(NAME): obj $(OBJ)
	make -C ../libft
	gcc $(OBJ) -o $(NAME) $(LIB)

obj:
	@mkdir obj

clean:
	@make -C ../libft clean
	rm -rf obj
	
fclean: clean
	@make -C ../libft fclean
	rm -f $(NAME)

re: fclean all
