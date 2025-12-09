# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/21 21:15:13 by jinwpark          #+#    #+#              #
#    Updated: 2025/02/21 21:15:16 by jinwpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

AR			=	ar rcs
RM			=	rm -f

SRCS		=	ft_atoi.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_strlen.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_bzero.c \
				ft_strncmp.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strnstr.c \
				ft_memset.c \
				ft_memmove.c \
				ft_memcpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_itoa.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_strmapi.c \
				ft_split.c

OBJS		=	$(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(AR) $@ $?


all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all
