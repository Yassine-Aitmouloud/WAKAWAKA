/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:59:00 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/11 18:48:55 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

typedef enum s_type
{
	TEST,
	WORD,
	BUILTIN,
	ARGUMENT,
	PIPE,
	HERE_DOC,
	DELIMITER,
	APPEND,
	RED_IN,
	RED_OUT,
	FILE_NAME
} t_type;

typedef struct s_token
{
	char *token;
	t_type type;
	int index;
	struct s_token *next;
} t_token;

typedef struct s_list
{
	char *file_name;
	int infile;
	int outfile;
	int append;
	int heredoc;
	char *delimiter;
	struct s_list *next;
} t_file;

typedef struct s_execution
{
	char **args;
	int infile;
	int outfile;
	t_file *file;
	struct s_execution *next;
} t_execution;
typedef struct s_hr
{
	int i;
	char **path;
	int pipes[2][2];
} t_hr;

typedef struct s_status
{
	int status;
} t_status;

typedef struct s_envp
{
	char *key;
	char *value;
	int status;
	struct s_envp *next;
} t_envp;

extern t_envp *new_envp;
#include "libft.h"
#include "tokenizer.h"
#include "expantion.h"

void ft_execution(t_execution *list,int size);
void check_command_type(t_execution *list);
int is_valid(t_execution *list,char **path);
void scan_cmd(t_execution *list);
int execute_cmd(t_execution *list,char *cmd);
void print_error(char *name,char *error);
int is_dir(char *path);
t_status *g_status();
int ft_isdigit(int c);
int ft_isalpha(int c);
char *searchAndsave(char *var);
int search_in_env(char *var);
int change_in_env(char *var, char *buf);
void ft_exit(t_execution *input, int size);
int ft_redirection(t_file *file);
int if_builtin(char *cmd);
void ft_pwd();
void ft_unset(t_execution *list);
void ft_export(t_execution *list);
void is_builtin(char *cmd, t_execution *list, int size);
void ft_unset(t_execution *list);
char **listToArray();
void ft_env();
void ft_unset(t_execution *list);
t_envp *ft_create_envp(char **envp);
void ft_lstadd_back2(t_envp **lst, t_envp *new);
t_envp *new_element2(char *line);
int CountLenKey(char *line);
int count_pipe_line(t_execution *list);
int ft_lstsize_envp(t_envp *lst);
int ft_lstsize(t_execution *lst);
void execute_pipes(char **path, t_execution *list, int size);
char **get_path();
char **ft_split(char const *s, char c);
void execute_simple_cmnd(char **path, t_execution *list, int size);
void ft_free(char **ptr);
int ft_isprint(int c);
char **get_path();
const char *type_to_string(t_type type);
t_execution *pre_execution(t_token *tokens);
#endif