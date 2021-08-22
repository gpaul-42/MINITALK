# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpaul <gpaul@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/21 03:32:26 by gpaul             #+#    #+#              #
#    Updated: 2021/08/22 14:15:42 by gpaul            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_1			=	server
NAME_2			=	client



SRCS_1			=	main.c				\
					ft_convert_base.c	\
					ft_convert_base2.c
SRCS_2			=	main.c				\
					ft_convert_base.c	\
					ft_convert_base2.c

OBJS_1			=	${addprefix server_srcs/,${SRCS_1:.c=.o}}
OBJS_2			=	${addprefix client_srcs/,${SRCS_2:.c=.o}}

LD_FLAGS		=	-L libft
HEAD			=	-I includes -I libft

CC				=	gcc

CFLAGS			=	-Wall -Werror -Wextra -g -fsanitize=address

all				:	${NAME_1} ${NAME_2}

c.o			:
					${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

$(NAME_1)		:	${OBJS_1}
					@make -C libft
					${CC} ${CFLAGS} ${LD_FLAGS} ${OBJS_1} -o ${NAME_1} -lft

$(NAME_2)		:	${OBJS_2}
					@make -C libft
					${CC} ${CFLAGS} ${LD_FLAGS} ${OBJS_2} -o ${NAME_2} -lft
clean			:
					make clean -C libft
					@rm -rf ${OBJS_1} ${OBJS_2}

fclean			:	clean
					make fclean -C libft
					@rm -rf ${NAME_1} ${NAME_2}

re				:	fclean all
