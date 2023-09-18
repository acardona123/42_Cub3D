NAME		=	cub3D

CC			=	cc
CFLAGS		=	-Werror -Wall -Wextra
DEPSFLAG	=	-MMD



FILES_PARSING	=	$(addprefix parsing/, \
					parse \
					)

FILES_TOOLS		=	$(addprefix tools/, \
					 \
					)

FILES_NAMES		=	main \
					$(FILES_PARSING) \
					$(FILES_TOOLS)



SRC_DIR		=	src
SRC			=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES_NAMES)))

OBJ_DIR		=	obj
OBJ			=	$(addprefix $(OBJ_DIR)/, $(FILES_NAMES:=.o))
DEPS		=	$(addprefix $(OBJ_DIR)/, $(FILES_NAMES:=.d))

all : $(NAME)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

-include $(DEPS)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(DEPSFLAG) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c Makefile
	@mkdir -p $(OBJ_DIR)
	@if [ ! -d "$(dir $@)" ]; then mkdir $(dir $@); fi
	$(CC) $(CFLAGS) $(DEPSFLAG) -c $< -o $@

.PHONY : all clean fclean re
