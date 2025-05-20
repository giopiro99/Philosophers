# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/04 12:57:19 by gpirozzi          #+#    #+#              #
#    Updated: 2025/03/27 10:21:37 by gpirozzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread
NAME = philo
SRC = philo.c parsing.c init_data.c safe_read.c syncro.c utils.c monitor.c dinner.c\

OBJ_DIR = obj
OBJECTS = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
		@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
		@echo "creating the objects file.."

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
		@$(CC) -c $(CFLAGS) -I. $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

clean:
		@rm -rf $(OBJ_DIR)
		@echo "cleaning...."

fclean: clean
		@rm -f $(NAME)
		@echo "all clean.."

re: fclean all

.PHONY: all clean fclean re
