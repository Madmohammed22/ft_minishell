NAME = minishell

BUILTIN_DIR = ft_builtins_helper
PARSING_DIR = ft_pars_minishell
EXECUTE_DIR = ft_execute_minishell

SRC = ft_minishell.c \
      $(PARSING_DIR)/ft_new_split.c \
      $(PARSING_DIR)/ft_split_utils.c \
      $(PARSING_DIR)/ft_syntax.c \
      $(PARSING_DIR)/ft_syntax_utils.c \
      $(PARSING_DIR)/ft_lstnew_v1.c \
      $(PARSING_DIR)/ft_rediction_utils.c \
      $(PARSING_DIR)/ft_rediction.c \
      $(PARSING_DIR)/ft_tree.c \
      $(EXECUTE_DIR)/ft_heredoc.c \
      $(EXECUTE_DIR)/ft_exection.c \
      $(EXECUTE_DIR)/ft_exection_utils.c \
      $(EXECUTE_DIR)/ft_pipe.c \
      $(EXECUTE_DIR)/ft_command.c \
      $(EXECUTE_DIR)/ft_command_utils2.c \
      $(EXECUTE_DIR)/ft_command_utils.c \
      $(BUILTIN_DIR)/ft_pwd.c \
      $(BUILTIN_DIR)/ft_builting.c \
      $(BUILTIN_DIR)/ft_exit.c \
      $(BUILTIN_DIR)/ft_export.c \
      $(BUILTIN_DIR)/ft_export_utilis_1.c \
      $(BUILTIN_DIR)/ft_export_utils2.c \
      $(BUILTIN_DIR)/ft_export_utils4.c \
      $(BUILTIN_DIR)/ft_export_utils.c \
      $(BUILTIN_DIR)/ft_cd.c \
      $(BUILTIN_DIR)/ft_echo.c \
      $(BUILTIN_DIR)/ft_echo_utils.c \
      $(BUILTIN_DIR)/ft_unset.c \
      $(BUILTIN_DIR)/signals.c \
      $(BUILTIN_DIR)/wild_card.c 

OBJECTS = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

all:  $(NAME)



$(OBJECTS): %.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 



$(NAME): $(OBJECTS)
	@make -s -C libft
	@make -s bonus -C libft
	@$(CC) $(CFLAGS) $(OBJECTS) libft/libft.a -lreadline -o $(NAME)

clean:
	@make -s clean -C libft
	@rm -rf $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 

.SECONDARY: $(OBJECTS)
