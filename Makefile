# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osamoile <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/01 15:53:40 by osamoile          #+#    #+#              #
#    Updated: 2018/08/23 19:21:36 by osamoile         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			osamoile.filler
HEADER =		-I ./includes \
				-I ./libft/includes
FLAGS =			-Wall -Werror -Wextra
LIB =			-lft -L ./libft
LIST =			main
OBJ =			$(addprefix obj/, $(addsuffix .o, $(LIST)))

all: $(NAME)

obj/%.o: src/%.c
	@gcc $(FLAGS) -c $< -o $@ $(HEADER)

$(NAME): obj $(OBJ)
	@make -C libft
	@gcc $(OBJ) -o $(NAME) $(LIB)

obj:
	@mkdir obj

clean:
	@make -C libft clean
	@rm -rf obj
	
fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all
