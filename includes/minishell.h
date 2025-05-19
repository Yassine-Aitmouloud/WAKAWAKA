/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:59:00 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/19 19:17:20 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "type.h"
# include "expantion.h"
# include "tokenizer.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
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
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include "here_doc.h"
# include "libft.h"
# include "header.h"
# define ALLOC 409600

void	no_args(t_execution *list);
int	ft_open(char *file_name, int flag);
char		*ft_itoa(int n);
t_status	*g_status(void);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
char		*searchAndsave(char *var);
int			search_in_env(char *var);
int			change_in_env(char *var, char *buf);
void		ft_exit(t_execution *input, int size);
int		ft_redirection(t_file *file);
int			if_builtin(char *cmd);
void		ft_pwd(void);
void		ft_unset(t_execution *list);
void		ft_export(t_execution *list);
void		is_builtin(char *cmd, t_execution *list, int size);
void		ft_unset(t_execution *list);
char		**listToArray(void);
void		ft_env(void);
void		ft_unset(t_execution *list);
t_envp		*ft_create_envp(char **envp);
void		ft_lstadd_back2(t_envp **lst, t_envp *new);
t_envp		*new_element2(char *line);
int			CountLenKey(char *line);
int			count_pipe_line(t_execution *list);
int			ft_lstsize_envp(t_envp *lst);
int			ft_lstsize(t_execution *lst);
void		execute_pipes(char **path, t_execution *list, int size);
char		**get_path(void);
char		**ft_split(char const *s, char c);
void		execute_simple_cmnd(char **path, t_execution *list, int size);
void		ft_free(char **ptr);
int			ft_isprint(int c);
char		**get_path(void);
void		ft_execution(t_execution *list, int size);
const char	*type_to_string(t_type type);
t_execution	*pre_execution(t_token *tokens);
t_token		*handle_heredoc(t_token *tokens);
void		ft_freeEnvp(void);
void		print(t_execution *list, t_token *list2);
void	check_command_type(t_execution *list);
void check_builtin(t_execution *list, int size);
void setup_pipes(int pipes[2][2], int i, int size,t_execution *list);
void execute_Cmd(t_execution *list, t_hr hr,int size);
void	close_previous(int pipes[2][2], int i);
void	wait_all(pid_t *pids, t_hr hr);
int	check_sen(char *list);
void	print_error(char *name, char *error);
void	execute_commands(t_execution *list, t_hr hr, int pipes[2][2], int size);
t_envp	*ft_lstlast2(t_envp *lst);
void	scan_cmd(t_execution *list);
void handler(int sig);
void sig_child();
void	cleanup(pid_t *pid, t_hr hr);
int	already_in(char *arg);
int	checkifnum(char *number);
void	ft_echo(t_execution *input);
void	ft_chdir(t_execution *input);
int	is_dir(char *path);
int	is_valid(t_execution *list);
void	execute_pipeline(int pipes[2][2], t_execution *list, t_hr helper,
		int size);
int	execute_cmd(t_execution *list, char *cmd);
#endif
