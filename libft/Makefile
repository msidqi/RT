# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msidqi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/12 11:43:36 by msidqi            #+#    #+#              #
#    Updated: 2019/10/11 11:06:16 by msidqi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC_PATH = src
SRC = ft_isascii.c ft_lstadd.c ft_memcmp.c ft_putnbr.c ft_strchr.c \
ft_strjoin.c ft_strnew.c ft_wordcount.c ft_isdigit.c ft_lstdel.c ft_memcpy.c \
ft_putnbr_fd.c ft_strclr.c ft_strlcat.c ft_strnstr.c ft_alert.c ft_islower.c \
ft_lstdelone.c ft_memdel.c ft_putstr.c ft_strcmp.c ft_strlen.c ft_strrchr.c \
ft_atoi.c ft_isprint.c ft_lstiter.c ft_memmove.c ft_putstr_fd.c ft_strcpy.c \
ft_strmap.c ft_strsplit.c ft_bzero.c ft_isupper.c ft_lstmap.c ft_memset.c \
ft_puttwodtab.c ft_strdel.c ft_strmapi.c ft_strstr.c ft_charcount.c \
ft_iterative_power.c ft_lstnew.c ft_putchar.c ft_sort_params.c ft_strdup.c \
ft_strncat.c ft_strsub.c ft_free_tab.c ft_itoa.c ft_memalloc.c \
ft_putchar_fd.c ft_split_whitespaces.c ft_strequ.c ft_strncmp.c ft_strtrim.c \
ft_isalnum.c ft_itoa_base.c ft_memccpy.c ft_putendl.c ft_sqrt.c ft_striter.c \
ft_strncpy.c ft_tolower.c ft_isalpha.c ft_link_two_lists.c ft_memchr.c \
ft_putendl_fd.c ft_strcat.c ft_striteri.c ft_strnequ.c ft_toupper.c
SRC_FILES = %.c
OBJS_DIR = .obj
OBJ = $(addprefix $(OBJS_DIR)/,$(SRC:.c=.o))
CC = gcc -Wall -Wextra -Werror
H_PATH = ../include

all: $(NAME)

$(OBJ) : $(OBJS_DIR)/%.o : $(SRC_PATH)/%.c | $(OBJS_DIR)
	$(CC) -c $^ -o $@ -I$(H_PATH)
$(NAME) : $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

$(OBJS_DIR):
	mkdir $(OBJS_DIR)
