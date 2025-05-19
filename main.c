/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:57:18 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/19 20:06:02 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
t_envp *g_new_envp;

int	ft_line_verifier(char *buf)
{
	int	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*my_ft_strjoin(char const *s1, char const *s2)
{
	t_gnl	data;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (strdup(s2));
	if (!s2)
		return (strdup(s1));
	data.lenstr = ft_strlen(s1) + ft_strlen(s2);
	data.str = (char *)calloc(1, data.lenstr + 1);
	if (!data.str)
		return (NULL);
	data.i = 0;
	while (s1[data.i])
	{
		data.str[data.i] = s1[data.i];
		data.i++;
	}
	data.y = 0;
	while (s2[data.y])
		data.str[data.i++] = s2[data.y++];
	data.str[data.i] = '\0';
	return (data.str);
}

char	*ft_read(int fd, char *buf)
{
	char	*tmp;
	ssize_t	b;

	while (1)
	{
		tmp = (char *)calloc(1, (size_t)(BUFFER_SIZE) + 1);
		b = read(fd, tmp, BUFFER_SIZE);
		if (b == -1)
			return (NULL);
		tmp[b] = '\0';
		buf = my_ft_strjoin(buf, tmp);
		if (!buf)
			return (NULL);
		if (ft_line_verifier(buf) == 1 || (b != BUFFER_SIZE))
			return (buf);
	}
	return (NULL);
}

char	*ft_saver(char **str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	if (((*str)[i] == '\0' && ft_line_verifier((*str)) == 0)
		|| ((*str)[i] != '\0' && (*str)[i + 1] == '\0'))
		return (NULL);
	(*str) = strdup((*str) + (i + 1));
	return ((*str));
}

char	*line_extracter(char *str)
{
	t_gnl	data;

	if (!str || str[0] == '\0')
		return (NULL);
	data.i = 0;
	data.j = 0;
	while (str[data.i] != '\n' && str[data.i] != '\0')
		data.i++;
	data.line = (char *)calloc(1, (size_t)(data.i + 1
				+ (str[data.i] == '\n')));
	if (!data.line)
		return (NULL);
	data.i = 0;
	while (str[data.i] != '\n' && str[data.i] != '\0')
		data.line[data.j++] = str[data.i++];
	if (str[data.i] == '\n')
		data.line[data.j++] = '\n';
	data.line[data.j] = '\0';
	return (data.line);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		buf = NULL;
		return (line);
	}
	buf = ft_read(fd, buf);
	if (!buf || buf[0] == '\0')
	{
		buf = NULL;
		return (line);
	}
	line = line_extracter(buf);
	if (!line)
		return (NULL);
	buf = ft_saver(&buf);
	return (line);
}

char	*read_input(void)
{
	char	*line;

	if (isatty(fileno(stdin)))
	{
		return (readline("sidi shellshell :"));
	}
	else
	{
		line = get_next_line(0);
		if (ft_strlen(line))
			line[ft_strlen(line) - 1] = '\0';
		return (line);
	}
}

const char *type_to_string(t_type type)
{
    if (type == BUILTIN)
        return "BUILTIN";
    else if (type == PIPE)
        return "PIPE";
    else if (type == RED_IN)
        return "RED_IN";
    else if (type == RED_OUT)
        return "RED_OUT";
    else if (type == FILE_NAME)
        return "FILE_NAME";
	else if (type == HERE_DOC)
        return "HERE_DOC";
	else if (type == DELIMITER)
        return "DELIMITER";
	else if (type == APPEND)
        return "APPEND";
	else if (type == ARGUMENT)
        return "ARGUMENT";
    return "WORD";
}

void print(t_execution *list, t_token *list2)
{
    int i;
    
    while (list2)
    {
        if (list2->token[0] == '\0' && !list2->expanded)
            printf("a7a\n");
        else
            printf("{%s} %s [%d]\n", type_to_string(list2->type), list2->token, list2->index);
        list2 = list2->next;
    }
    if (list)
    {   
        while (list)
        {
                i = 0;
                while (list->args[i])
                {
                    printf("%s ", list->args[i]);
                    i++;
                }
                
                printf("\n[%d]\n", list->infile);
            if (list->file)
            {
                t_file *iterate = list->file;
    
                while (iterate)
                { 
                    // printf("[%s] [%d] [%d] [%d] {%d}\n", iterate->file_name, iterate->infile, iterate->outfile, iterate->append, iterate->heredoc);
                    iterate = iterate->next;
                }
            }
            list = list->next;
        }
    }
}

int check_space(char *input)
{
    int i = 0;
    while (input[i] && (input[i] == ' ' || input[i] == '\t'))
          i++;
    if (input[i] == '\0')
        return 1;
    return 0;
}
void ft_freeEnvp()
{
    t_envp *temp;
    while (g_new_envp)
    {
        temp = g_new_envp;
        g_new_envp = g_new_envp->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
}
t_status *g_status()
{
    static t_status status = {0};
    return &status;
}

void handler(int sig)
{
	
    (void)sig;
    if (g_status()->flag == 0)
    {
        printf("\n");                
        rl_on_new_line();            
        rl_replace_line("", 0);      
        rl_redisplay();              
        g_status()->status = 130;    
    }
    else
        return;
}


void sig_child()
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*input;
	t_token	*tokens = NULL;
	t_execution	*pre = NULL;
    g_new_envp = NULL;
    g_new_envp = ft_create_envp(envp);
	while (1)
	{
        signal(SIGINT, handler);
        signal(SIGQUIT, SIG_IGN);
        g_status()->flag = 0;
        // input = read_input();
        input = readline("minishell $>: ");
        if (!input)
        {
            if (isatty(STDIN_FILENO))
                write(2,"exit",4);
			exit(g_status()->status);
            ft_freeEnvp();
        }
		add_history(input);
        g_status()->flag = 1;
		if (check_quotes(input))
		{
			ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
            g_status()->status = 2;
            free(input);
			continue;
		}
		tokens = tokenizer(input, tokens);
        if (parser(tokens))
        {
            ft_lstclear(&tokens, free);
            // free(input);
        }
		tokens = handle_heredoc(tokens);
		if (!tokens)
		{
			ft_lstclear(&tokens, free);
            free(input);
			continue;
		}
		tokens = expantion(tokens);
		pre = pre_execution(tokens);
		// print(pre, tokens);
        check_command_type(pre);
		ft_lstclear(&tokens, free);
		ft_lstclear_v2(&pre);
		free(input);
	}
    ft_freeEnvp();
}
