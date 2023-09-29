NAME = libft.a

CC = cc
C_FLAGS = -Wall -Wextra -Werror

C_ROOT = ft_atoi ft_atoi_protected ft_atoui_protected ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_itoa ft_iswhitespace ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd ft_split ft_strchr ft_strdup ft_striteri ft_strjoin ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp ft_strcmp ft_strnstr ft_strrchr ft_strtrim ft_substr ft_tolower ft_toupper ft_atoi_long ft_int_abs ft_ptrswap ft_strjoin3 ft_strlst_free ft_strlst_len ft_itoa_simple ft_isinset ft_strndup ft_strjoin_free ft_strlst_disp ft_tabfree ft_tablen get_next_line get_next_line_utils

C_ROOT_BONUS = ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back ft_lstdelone ft_lstclear ft_lstiter ft_lstmap ft_lstnewaddback ft_lstprint

C_FILES = $(addsuffix .c, $(C_ROOT))
C_FILES_BONUS = $(addsuffix .c, $(C_ROOT_BONUS))

O_FILES = $(C_FILES:c=o)
O_FILES_BONUS = $(C_FILES_BONUS:c=o)

LIBFT = libft/libft.a

H_INCLUDES = ./libft.h

all: ${NAME}

%.o: %.c ${H_INCLUDES}
	${CC} ${C_FLAGS} -c $< -o $@

${NAME}: $(O_FILES)
	ar rcs $(NAME) ${O_FILES}

bonus : $(O_FILES) $(O_FILES_BONUS) 
	ar rcs $(NAME) ${O_FILES} $(O_FILES_BONUS)

clean:
	@rm -f $(O_FILES) $(O_FILES_BONUS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re debug bonus
