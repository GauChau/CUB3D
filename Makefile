# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 12:09:20 by gautierchau       #+#    #+#              #
#    Updated: 2025/01/17 14:09:17 by gchauvot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OUT = parser


SRC = get_next_line_utils_bonus.c get_next_line_bonus.c parsing_cubed.c floor_ceiling.c map_parser.c textures_parser.c
SRC_OBJS = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -g
HEADER = -I. -I$(LIBFT_DIR)
LIBFT_DIR = Libft/
LIBFT = $(LIBFT_DIR)libft.a

all: $(LIBFT) $(OUT)

$(LIBFT):
	@echo "Making Libft.."
	@make -C $(LIBFT_DIR)

$(OUT): $(SRC_OBJS)
	cc $(FLAGS) $(SRC_OBJS) $(HEADER) -lreadline -o $(OUT) $(LIBFT)

$(SRC_OBJS): %.o: %.c
	cc $(FLAGS) $(HEADER) -c $< -o $@

clean:
	rm -f $(SRC_OBJS)

fclean: clean
	rm -f $(OUT)

re: fclean all
