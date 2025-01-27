# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 21:19:02 by julessainth       #+#    #+#              #
#    Updated: 2024/12/11 15:59:07 by jsaintho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBC =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_apply_rmquote.c \
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
		ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
		ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_strcmp.c \
		ft_strchr.c ft_atoi_l.c ft_m_strchr_i.c ft_putendl.c ft_memdel.c \
		get_next_line_bonus.c get_next_line_utils_bonus.c ft_rm_quotes.c \
		ft_last_strchr_i.c ft_strjoin_free.c ft_multisplit.c ft_splitter.c ft_putquote.c \
		ft_str_remvchr.c ft_str_isalpha.c ft_inq.c ft_char_in_set.c ft_free_multisplit.c ft_free_split.c \
		ft_free_tab.c ft_stronly.c ft_str_isalnum.c

ADDITIONAL =	ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
				ft_split.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_substr.c ft_striteri.c


BONUS =	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
		ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
		ft_lstmap.c ft_lstnew.c ft_lstsize.c

SRCS = ${LIBC} ${ADDITIONAL}
SRCSALL = ${LIBC} ${ADDITIONAL} ${BONUS}

OBJS = ${SRCS:.c=.o}
OBJSALL = ${SRCSALL:.c=.o} 

NAME = libft.a

CC = cc

CFLAGS = -Wall -Werror -Wextra -I ./

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
	
all: $(NAME)

${NAME}: ${OBJS}
		ar -rsc ${NAME} ${OBJS}

bonus: ${OBJSALL}
		ar -rsc ${NAME} ${OBJSALL}

clean:	
		rm -f ${OBJSALL}

fclean:	clean;
		rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re bonus
