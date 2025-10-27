# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/31 10:02:01 by dbakker           #+#    #+#              #
#    Updated: 2025/09/29 14:28:57 by dbakker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo

SRCDIR	:= src
OBJDIR	:= obj

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror #-fsanitize=thread -g
HEADERS	:= -I include

SRCS	:= \
	checker.c \
	clear_table.c \
	init_utils.c \
	init.c \
	isthing.c \
	main.c \
	monitor.c \
	print.c \
	routine.c \
	status_utils.c \
	status.c \
	utils.c \

SRCPATH	:= $(addprefix $(SRCDIR)/,$(SRCS))
OBJS	:= $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCPATH:.c=.o))

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\e[32m"$(NAME) compiled"\e[0m"

clean:
	@rm -rf $(OBJDIR)
	@echo "\e[32m"$(OBJDIR) cleaned"\e[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\e[32m"$(NAME) cleaned"\e[0m"

re: fclean all

.PHONY: all clean fclean re