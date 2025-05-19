NAME = minishell

CC = cc -ggdb #-fsanitize=address 

# CFLAGS = -Wall -Wextra -Werror -ggdb

MINISHELL_SRC = main.c

TOKENIZER = tokenizer/tokenizer.c parser/parser.c parser/parser_utils.c parser/pre_execution.c tokenizer/lexer.c tokenizer/tokenizer_utils.c here_doc/here_doc.c

EXPANTION = expantion/expantion.c

LIBFT_SRC = libft/ft_lstaddback.c libft/ft_lstdelone.c libft/ft_lstnew.c libft/ft_strjoin.c libft/ft_strlcpy.c libft/ft_strndup.c \
            libft/ft_lstclear.c libft/ft_lstlast.c libft/ft_strchr.c libft/ft_strlcat.c libft/ft_strlen.c \
            libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_strncmp.c libft/ft_split.c libft/ft_lstsize.c libft/ft_atoi.c \
			libft/ft_isalpha.c libft/ft_substr.c  libft/alphanum.c libft/ft_itoa.c

EXECUTIN_SRC = execution/ft_simple_command.c execution/ft_execution.c execution/execute_pipes.c execution/builtins.c execution/builtins2.c \
			   execution/builtinsUtils.c execution/builtinsUtils2.c execution/controlEnvp.c execution/controlEnvp2.c execution/execute_cmnds.c \
			   execution/execute_cmnds2.c 

EXECUTION_OBJ = $(EXECUTIN_SRC:.c=.o)

MINISHELL_OBJ = $(MINISHELL_SRC:.c=.o)

EXPANTION_OBJ = $(EXPANTION:.c=.o)

LIBFT_OBJ = $(LIBFT_SRC:.c=.o)

TOKENIZER_OBJ = $(TOKENIZER:.c=.o)

all: $(NAME)

$(NAME):	$(MINISHELL_OBJ)	$(LIBFT_OBJ)	$(TOKENIZER_OBJ)	$(EXECUTION_OBJ) $(EXPANTION_OBJ)
	$(CC)	$(CFLAGS)	$^	-lreadline 	-o	$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -I./includes $< -o $@

clean:
	rm -rf $(MINISHELL_OBJ) $(LIBFT_OBJ) $(TOKENIZER_OBJ) $(EXECUTION_OBJ) $(EXPANTION_OBJ)

fclean: clean
	rm -rf $(NAME)

.PHONY: all clean fclean re

re: fclean all

.SECONDARY: $(MINISHELL_OBJ) $(LIBFT_OBJ) $(TOKENIZER_OBJ) $(EXECUTION_OBJ) $(EXPANTION_OBJ)
