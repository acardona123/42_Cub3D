NAME			=	cub3D

CC				=	cc
CFLAGS			=	-Werror -Wall -Wextra -g
DEPSFLAG		=	-MMD

MLX_DIR			=	mlx
MLX				=	$(MLX_DIR)/libmlx.a
LIBFT_DIR		=	libft
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
							init_utils \
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
								static_texture \
								set_color \
								check_texture_defined \
								utils \
							) \
							$(addprefix 3_mapcontent/init_3_mapcontent_, \
								main \
								fill_chunk \
								locate_texture \
								set_status_action \
							) \
							$(addprefix 4_minimap/init_4_minimap_, \
								main \
							) \
						)

FILES_RAY_COLLISION	=	$(addprefix ray_collision/ray_collision_, \
							main \
							init \
							segments_east \
							segments_west \
							hit_check \
							hit_check_door \
							utils \
						)

FILES_RAYCASTING	=	$(addprefix raycasting/raycasting_, \
							frame_build \
							use_texture \
						)


FILES_GAMEPLAY		=	$(addprefix gameplay/gameplay_, \
							main \
							turn_head \
							walk \
							action \
						)

FILES_TOOLS		=	$(addprefix tools/tools_, \
						error \
						vectors \
						lst \
						time \
						angles_set \
					)

FILES_DOORS		=	$(addprefix doors/doors_, \
						update \
						action \
					)

FILES_MAP		=	$(addprefix map/map_, \
						main \
						get_pixel_color \
						update_world \
					)

FILES_NAMES			=	\
						$(FILES_INIT) \
						$(FILES_END_DESTROY) \
						$(FILES_TOOLS) \
						$(FILES_RAY_COLLISION) \
						$(FILES_RAYCASTING) \
						$(FILES_GAMEPLAY) \
						$(FILES_DOORS) \
						$(FILES_MAP) \
						main 


SRC_DIR			=	src
SRC				=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES_NAMES)))

OBJ_DIR			=	obj
OBJ				=	$(addprefix $(OBJ_DIR)/, $(FILES_NAMES:=.o))
DEPS			=	$(addprefix $(OBJ_DIR)/, $(FILES_NAMES:=.d))


STATE_FILE = $(OBJ_DIR)/.state

all : all_state lib_mlx lib_libft name_start $(NAME) name_end
	@echo "all" > $(STATE_FILE)
	@echo Done

bonus : bonus_state lib_mlx lib_libft name_start $(NAME) name_end
	@echo "bonus" > $(STATE_FILE)
	@echo done

all_state :
	@mkdir -p $(OBJ_DIR)
	@if [ ! -f $(STATE_FILE) ]; then \
		echo all > $(STATE_FILE); \
	fi
	@if [ "$$(cat $(STATE_FILE))" != "all" ]; then \
		rm -rf $(OBJ_DIR) $(NAME); mkdir $(OBJ_DIR); echo "all" > $(STATE_FILE); \
	fi

bonus_state :
	@mkdir -p $(OBJ_DIR)
	@if [ ! -f $(STATE_FILE) ]; then \
		echo bonus > $(STATE_FILE); \
	fi
	@if [ "$$(cat $(STATE_FILE))" != "bonus" ]; then \
		rm -rf $(OBJ_DIR) $(NAME); mkdir $(OBJ_DIR); echo "bonus" > $(STATE_FILE); \
	fi

lib_mlx :
	@echo "\e[32m==== MLX CLONING AND COMPILATION ====\e[0m"
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

lib_libft :
	@echo "\e[32m==== LIBFT COMPILATION ====\e[36m"
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "\e[32m---- End: libft compilation ----\e[0m\n"

clean :
	@echo "\e[31mRemoving object files\e[0m"
	@rm -rf $(OBJ_DIR)
	@make clean --no-print-directory -C $(LIBFT_DIR)
	@make clean --no-print-directory -C $(MLX_DIR) >/dev/null 2>&1

fclean : clean
	@echo "\e[31mRemoving Libft library, mlx directory and executable\e[0m"
	@rm -rf $(NAME)
	@rm -rf $(MLX_DIR)
	@make fclean --no-print-directory -C $(LIBFT_DIR)

re : fclean all

-include $(DEPS)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(DEPSFLAG) $(OBJ) $(INCLUDE_LIB) -o $(NAME)


name_start :
	@echo "\e[32m==== SOURCES COMPILATION ====\e[0m"

name_end :
	@echo "\e[32m---- End: sources compilation ----\e[0m\n"

ifeq ($(MAKECMDGOALS),bonus)
CFLAGS += -D BONUS
endif

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c Makefile
	@mkdir -p $(OBJ_DIR)
	@if [ ! -d "$(dir $@)" ]; then mkdir $(dir $@); fi
	$(CC) $(CFLAGS) $(DEPSFLAG) -c $< -o $@


.PHONY : all clean fclean re bonus