NAME			=	cub3D

CC				=	cc
CFLAGS			=	-Werror -Wall -Wextra
DEPSFLAG		=	-MMD

INCLUDE_LIB		=	-L$(MLX_DIR) -lmlx -lmlx -lXext -lX11 -lm


FILES_PARSING	=	$(addprefix parsing/, \
					)

FILES_TOOLS		=	$(addprefix tools/, \
					 \
					)

FILES_NAMES		=	main \
					$(FILES_PARSING) \
					$(FILES_TOOLS)


SRC_DIR			=	src
SRC				=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES_NAMES)))

OBJ_DIR			=	obj
OBJ				=	$(addprefix $(OBJ_DIR)/, $(FILES_NAMES:=.o))
DEPS			=	$(addprefix $(OBJ_DIR)/, $(FILES_NAMES:=.d))

MLX_DIR			=	mlx

all : MLX $(NAME)

MLX :
	@echo "\e[32m==== MLX CLONING AND COMPIATION ====\e[0m"
	@if [ ! -d "$(MLX_DIR)" ]; then \
        echo "Cloning the mlx..."; \
        git clone -q https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
    else \
        echo "Pulling the mlx..."; \
        (cd $(MLX_DIR) && git pull); \
    fi
	@echo "Compiling the mlx..."
	@make --no-print-directory -C $(MLX_DIR) >/dev/null 2>/dev/null
	@echo "\e[32m---- End: mlx cloning and compilation ----\e[0m\n"

clean :
	@echo "\e[31mRemoving object files\e[0m"
	@rm -rf $(OBJ_DIR)

	@make clean --no-print-directory -C $(MLX_DIR) >/dev/null 2>&1

fclean : clean
	@echo "\e[31mRemoving mlx library and \e[0m"
	@if [ -d "$(MLX_DIR)" ]; then \
		rm -rf $(NAME) $(MLX_DIR);\
	fi

re : fclean all

-include $(DEPS)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(DEPSFLAG) $(OBJ) $(INCLUDE_LIB) -o $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c Makefile
	@mkdir -p $(OBJ_DIR)
	@if [ ! -d "$(dir $@)" ]; then mkdir $(dir $@); fi
	$(CC) $(CFLAGS) $(DEPSFLAG) -c $< -o $@

.PHONY : all clean fclean re