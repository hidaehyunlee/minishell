# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/09 18:24:09 by daelee            #+#    #+#              #
#    Updated: 2021/01/31 17:44:06 by daelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	= 	main.c \
			builtins/ft_echo.c\
			builtins/ft_env.c \
			builtins/ft_pwd.c \
			builtins/ft_cd.c \
			builtins/ft_exit.c \
			builtins/ft_export.c \
			builtins/ft_unset.c \
			execute/exec_cmds.c \
			utils/utils_envv.c \
			utils/utils_signal.c \
			errors/envv_err.c \
			errors/execute_err.c \
			errors/exit_err.c \
			parser/parser.c \
			parser/parse_error.c \

LIBFT	=	libft.a

LIBS	=	-L./Libft -lft

HEADER	=	-I./

FLAG	= 	-Wall -Wextra -Werror

CC		=	gcc

RM		=	rm -rf

DEBUG	=	-g -fsanitize=address

all		: $(NAME)

$(LIBFT):
	$(MAKE) -C ./Libft

$(NAME)	: $(LIBFT)
	$(CC) $(SRCS) $(LIBS) $(HEADER) $(FLAG) $(DEBUG) -o $(NAME) 

clean	:
	$(MAKE) -C ./Libft clean
	rm -rf $(OBJS)

fclean	:
	$(MAKE) -C ./Libft fclean
	rm -rf $(NAME)

re		: fclean all
