NAME			=	cub3D

CC				=	cc
CFLAGS			=	-Werror -Wall -Wextra -g
DEPSFLAG		=	-MMD

MLX_DIR			=	mlx
MLX				=	$(MLX_DIR)/libmlx.a
LIBFT_DIR		=	libft
LIBFT			=	$(LIBFT_DIR)/libft.a
INCLUDE_LIB		=	-L$(MLX_DIR) -lmlx -lXext -lX11 -lm -L$(LIBFT_DIR) -lft


FILES_END_DESTROY	=	$(addprefix end_destroy/end_destroy_, \
							general \
							display \
							exit \
							map \
							texture_pack \
						)

FILES_INIT			=	$(addprefix init/, \
							init_main \
							$(addprefix 0_user_interface/init_0_user_interface_, \
								main \
								hooks \
							) \
							$(addprefix 1_mapformat/init_1_mapformat_, \
								main \
								utils \
							) \
							$(addprefix 2_texturepack/init_2_texturepack_, \
								main \
								animated_texture \
								set_color \
								static_texture \
								tools \
							) \
							$(addprefix 3_mapcontent/init_3_mapcontent_, \
								main \
								utils \
							) \
						)

FILES_RAYCASTING	=	$(addprefix raycasting/raycasting_, \
							\
						)

FILES_TOOLS			=	$(addprefix tools/tools_, \
							error \
							vectors \
							lst \
							time \
						)

FILES_NAMES			=	main \
						$(FILES_INIT) \
						$(FILES_END_DESTROY) \
						$(FILES_TOOLS)


SRC_DIR			=	src
SRC				=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES_NAMES)))

OBJ_DIR			=	obj
OBJ				=	$(addprefix $(OBJ_DIR)/, $(FILES_NAMES:=.o))
DEPS			=	$(addprefix $(OBJ_DIR)/, $(FILES_NAMES:=.d))


all : $(MLX) $(LIBFT) $(NAME)

$(MLX) :
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

$(LIBFT) :
	@echo "\e[32m==== LIBFT COMPIATION ====\e[36m"
	@make -C $(LIBFT_DIR)
	@echo "\e[32m---- End: libft compilation ----\e[0m\n"

clean :
	@echo "\e[31mRemoving object files\e[0m"
	@rm -rf $(OBJ_DIR)
	@make clean --no-print-directory -C $(LIBFT_DIR)
	@make clean --no-print-directory -C $(MLX_DIR) >/dev/null 2>&1

fclean : clean
	@echo "\e[31mRemoving Libft library and executable\e[0m"
	@rm -rf $(NAME)
	@make fclean --no-print-directory -C $(LIBFT_DIR)

re : fclean all

-include $(DEPS)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(DEPSFLAG) $(OBJ) $(INCLUDE_LIB) -o $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c Makefile
	@mkdir -p $(OBJ_DIR)
	@if [ ! -d "$(dir $@)" ]; then mkdir $(dir $@); fi
	$(CC) $(CFLAGS) $(DEPSFLAG) -c $< -o $@

.PHONY : all clean fclean re