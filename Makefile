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
INC =			-I ./includes \
				-I ./libft/includes
LIB =			-lft -L ./libft
FLAGS =			-Wall -Wextra -Werror
LIST =			main \
				read \
				create_map \
				distance \
				analyze \
				put_piece
OBJ =			$(addprefix obj/, $(addsuffix .o, $(LIST)))

all: $(NAME)

obj/%.o: src/%.c
	@gcc $(FLAGS) -c $< -o $@ $(INC)

$(NAME): obj $(OBJ)
	@make -C libft
	@make -C visualizer
	@gcc $(OBJ) -o $(NAME) $(LIB)

obj:
	@mkdir obj

clean:
	@make -C libft clean
	@make -C visualizer clean
	@rm -rf obj
	
fclean: clean
	@make -C libft fclean
	@make -C visualizer fclean
	@rm -f $(NAME)

re: fclean all
