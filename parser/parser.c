/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:49:01 by sfyn              #+#    #+#             */
/*   Updated: 2025/05/09 13:10:54 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

int	check_quotes(char *input)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (input[i])
	{
		if (input[i] == '\'' && in_double == 0)
		{
			if (in_single == 0)
				in_single = 1;
			else
				in_single = 0;
		}
		else if (input[i] == '\"' && in_single == 0)
		{
			if (in_double == 0)
				in_double = 1;
			else
				in_double = 0;
		}
		i++;
	}
	if (in_single || in_double)
	{
		g_status()->status = 130;
		return (1);
	}
	return (0);
}



int	parser(char *input)
{
	if (input[0] == '|' && input[1] != '|')
	{
		ft_putstr_fd("minishell: parse error near '|'\n", 2);
		return (1);
	}
	printf("test\n");
	return (0);
}

int	check_parenthis(char *input)
{
	int	i;
	int	open_parenthis;

	i = 0;
	open_parenthis = 0;
	while (input[i])
	{
		if (input[i] == ')' && open_parenthis == 0)
		{
			ft_putstr_fd("minishell: parse error near `)'\n", 2);
			return (1);
		}
		else if (input[i] == '(' && open_parenthis == 0)
		{
			i++;
			open_parenthis = 1;
			while (input[i] && input[i] != ')')
			{
				if (input[i] == '(')
				{
					ft_putstr_fd("minishell: parse error near `('\n", 2);
					return (1);
				}
				i++;
			}
			if (input[i] == ')' && input[i - 1] == '(')
			{
				ft_putstr_fd("minishell : (empty subshell)\n", 2);
				return (1);
			}
			else if (input[i] == ')')
				open_parenthis = 0;
		}
		i++;
	}
	if (input[i] == '\0' && open_parenthis == 1)
	{
		ft_putstr_fd("minishell : unclosed subshell `('\n", 2);
		return (1);
	}
	return (0);
}

int	count_words(t_token *tokens)
{
	t_token	*iterator;
	int		i;

	iterator = tokens;
	i = 0;
	while (iterator)
	{
		if (iterator->type == PIPE)
			break ;
		i++;
		iterator = iterator->next;
	}
	return (i);
}

t_execution	*create_element(t_token *tokens)
{
	t_execution	*element;

	element = malloc(sizeof(t_execution));
	if (!element)
		return (NULL);
	element->args = malloc(sizeof(char *) * (count_words(tokens) + 1));
	if (!element->args)
		return (NULL);
	element->infile = -2;
	element->outfile = -2;
	element->file = NULL;
	element->next = NULL;
	return (element);
}

int	open_file(char *file, int flag)
{
	int	fd = 0;
	if (flag == -1)
	{		
		fd = open(file, O_RDONLY);
		if (fd == -1)
			return (fd);
	}
	else if (flag == 0)
	{
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
			return (fd);
	}
	else if (flag == 1)
	{
		fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
			return (fd);
	}
	return (fd);
}

t_file	*create_element_file(char *filename)
{

	t_file	*element;
	(void)filename;
	element = malloc(sizeof(t_file));
	element->infile = 0;
	element->outfile = 0;
	element->append = 0;
	element->heredoc = 0;
	element->delimiter = NULL;
	element->next = NULL;
	return (element);
}

t_file	*ft_lstlast_v3(t_file *lst)
{
	t_file	*last_content;

	if (!lst)
		return (NULL);
	last_content = lst;
	while (last_content != NULL && last_content->next != NULL)
	{
		last_content = last_content->next;
	}
	return (last_content);
}

void	ft_lstadd_back_v3(t_file **lst, t_file *new)
{
	t_file	*last;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast_v3(*lst);
		last->next = new;
	}
}

void parse_file(t_token *token, t_execution *ex, int flag)
{
	t_file *element = NULL ;
	if (flag == RED_IN)
	{
		element = create_element_file(token->token);
		element->file_name = ft_strndup(token->token, ft_strlen(token->token));
		element->infile = 1;
		ft_lstadd_back_v3(&ex->file, element);
	}
	else 	if (flag == RED_OUT)
	{
		element = create_element_file(token->token);
		element->file_name = ft_strndup(token->token, ft_strlen(token->token));
		element->outfile = 1;
		ft_lstadd_back_v3(&ex->file, element);
	}
	else 	if (flag == APPEND)
	{
		element = create_element_file(token->token);
		element->file_name = ft_strndup(token->token, ft_strlen(token->token));
		element->append = 1;
		ft_lstadd_back_v3(&ex->file, element);
	}
}

t_token *copy_elements(t_execution *exec, t_token *iterate)
{
    int i = 0;
    int flag = 0;

    while (iterate)
    {
        if (iterate->type == PIPE)
            break;
        else if (iterate->type == RED_IN 
              || iterate->type == RED_OUT 
              || iterate->type == HERE_DOC 
              || iterate->type == APPEND)
        {
            flag = iterate->type;
            iterate = iterate->next;
            if (!iterate)
                break;
            parse_file(iterate, exec, flag);
            iterate = iterate->next;
            continue;
        }
        if (iterate && iterate->token)
        {
            exec->args[i] = ft_strndup(iterate->token, ft_strlen(iterate->token));
            i++;
        }
        iterate = iterate->next;
    }
    exec->args[i] = NULL;
    return (iterate);
}


t_execution	*ft_lstlast_v2(t_execution *lst)
{
	t_execution	*last_content;

	if (!lst)
		return (NULL);
	last_content = lst;
	while (last_content != NULL && last_content->next != NULL)
	{
		last_content = last_content->next;
	}
	return (last_content);
}

void	ft_lstadd_back_v2(t_execution **lst, t_execution *new)
{
	t_execution	*last;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast_v2(*lst);
		last->next = new;
	}
}

t_execution	*pre_execution(t_token *tokens)
{
	int i = 0;
	t_execution *exec_list = NULL;
	t_execution *temp = NULL;
	t_token *iterate = tokens;

	while (iterate)
	{
		if (iterate->type == PIPE)
			iterate = iterate->next;
		temp = create_element(iterate);
		iterate = copy_elements(temp, iterate);
		ft_lstadd_back_v2(&exec_list, temp);
		i++;
	}
	return (exec_list);
}