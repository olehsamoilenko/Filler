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
INC =			-I ../libft/includes -I ./includes
LIB =			-lncurses -lft -L ../libft
FLAGS =			-Wall -Wextra -Werror
LIST =			main \
				show \
				init
OBJ =			$(addprefix obj/, $(addsuffix .o, $(LIST)))

all: $(NAME)

obj/%.o: src/%.c
	@gcc $(FLAGS) -c $< -o $@ $(INC)

$(NAME): obj $(OBJ)
	@gcc $(OBJ) -o $(NAME) $(LIB)

obj:
	@mkdir obj

clean:
	@rm -rf obj
	
fclean: clean
	@rm -f $(NAME)

re: fclean all
