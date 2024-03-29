# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malord <malord@student.42quebec.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/20 10:07:57 by malord            #+#    #+#              #
#    Updated: 2022/08/17 09:18:21 by malord           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
LIBFT		=	libft/libft.a

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -f

SRCS		=	pipex.c	\
				utils.c

OBJS		= 	${SRCS:.c=.o}

# Targets

.c.o:
				@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): 		$(OBJS)
				@echo "Compiling libft..."
				@$(MAKE) -C libft
				@echo "libft compiled successfully."
				@echo "Compiling $(NAME) sources"
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
				@echo "Done !"

all: 			$(NAME)

# Removes objects
clean:
				@echo "Removing $(NAME) objects..."
				@$(RM) $(OBJS)
				@echo "Removing libft objects..."
				@make clean -C libft
				@echo "$(NAME) objects successfully deleted."
				@echo "libft objects successfully deleted."

# Removes objects and executable
fclean: 		clean
				@echo "Removing $(NAME) program..."
				@$(RM) $(NAME)
				@echo "Removing libft archive..."
				@$(RM) $(LIBFT)
				@echo "Executable(s) and archive(s) successfully deleted."

# Removes objects and executable then remakes all
re: 			fclean all
				
.PHONY:			all clean fclean bonus re				