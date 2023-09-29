NAME = libft.a

CC 			=	cc
C_FLAGS		=	-Wall -Wextra -Werror
DEPSFLAG	=	-MMD

FILES_NAMES	=	ft_atoi \
				ft_atoi_protected \
				ft_atoui_protected \
				ft_bzero \
				ft_calloc \
				ft_isalnum \
				ft_isalpha \
				ft_isascii \
				ft_isdigit \
				ft_isprint \
				ft_itoa \
				ft_iswhitespace \
				ft_memchr \
				ft_memcmp \
				ft_memcpy \
				ft_memmove \
				ft_memset \
				ft_putchar_fd \
				ft_putendl_fd \
				ft_putnbr_fd \
				ft_putstr_fd \
				ft_split \
				ft_strchr \
				ft_strdup \
				ft_striteri \
				ft_strjoin \
				ft_strlcat \
				ft_strlcpy \
				ft_strlen \
				ft_strmapi \
				ft_strncmp \
				ft_strcmp \
				ft_strnstr \
				ft_strrchr \
				ft_strtrim \
				ft_substr \
				ft_tolower \
				ft_toupper \
				ft_atoi_long \
				ft_int_abs \
				ft_ptrswap \
				ft_strjoin3 \
				ft_strlst_free \
				ft_strlst_len \
				ft_itoa_simple \
				ft_isinset \
				ft_strndup \
				ft_strjoin_free \
				ft_strlst_disp \
				ft_tabfree \
				ft_tablen \
				get_next_line \
				get_next_line_utils \
				ft_lstnew \
				ft_lstadd_front \
				ft_lstsize \
				ft_lstlast \
				ft_lstadd_back \
				ft_lstdelone \
				ft_lstclear \
				ft_lstiter \
				ft_lstmap \
				ft_lstnewaddback \
				ft_lstprint

SRC		=	$(addsuffix .c, $(FILES_NAMES))

OBJ_DIR	=	obj
OBJ		=	$(addprefix $(OBJ_DIR)/, $(FILES_NAMES:=.o))
DEPS	=	$(addprefix $(OBJ_DIR)/, $(FILES_NAMES:=.d))

all : $(NAME)

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

-include $(DEPS)

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o : %.c Makefile
	@mkdir -p $(OBJ_DIR)
	@if [ ! -d "$(dir $@)" ]; then mkdir $(dir $@); fi
	$(CC) $(CFLAGS) $(DEPSFLAG) -c $< -o $@

.PHONY: all clean fclean re debug
