/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:00:24 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/16 21:39:00 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expantion.h"

t_token	*handle_quote(t_token *tokens)
{
	t_token	*iterate;
	char	*temp;

	iterate = tokens;
	int i, j;
	while (iterate)
	{
		i = 0;
		j = 0;
		temp = malloc(ft_strlen(iterate->token) + 1);
		if (!temp)
			return (NULL);
		while (iterate->token[i])
		{
			if (iterate->token[i] == '"')
			{
				i++;
				while (iterate->token[i] && iterate->token[i] != '"')
				{
					temp[j] = iterate->token[i];
					j++;
					i++;
				}
				if (iterate->token[i] == '"')
					i++;
			}
			else if (iterate->token[i] == '\'')
			{
				i++;
				while (iterate->token[i] && iterate->token[i] != '\'')
				{
					temp[j] = iterate->token[i];
					j++;
					i++;
				}
				if (iterate->token[i] == '\'')
					i++;
			}
			else
			{
				temp[j] = iterate->token[i];
				j++;
				i++;
			}
		}
		temp[j] = '\0';
		free(iterate->token);
		iterate->token = ft_strndup(temp, j);
		free(temp);
		iterate = iterate->next;
	}
	return (tokens);
}

t_token	*expand_wildcard(t_token *token)
{
	t_token	*iterate;
	int		i;

	iterate = token;
	while (iterate)
	{
		i = 0;
		while (iterate->token[i])
		{
			if (iterate->token[i] == '*')
			{
				iterate->index = 1;
				break ;
			}
			i++;
		}
		iterate = iterate->next;
	}
	iterate = token;
	return (token);
}

int	find_dollar(char *s)
{
	while (*s)
	{
		if (*s == '$')
			return (1);
		s++;
	}
	return (0);
}

int	is_special(char c)
{
	return ((c == '$' || c == '"'));
}

char	*expand_env(char *key)
{
	t_envp	*iterate;

	iterate = g_new_envp;
	while (iterate)
	{
		if (ft_strlen(key) == ft_strlen(iterate->key) && ft_strncmp(key,
				iterate->key, ft_strlen(key)) == 0)
		{
			free(key);
			key = ft_strndup(iterate->value, ft_strlen(iterate->value));
			return (key);
		}
		else
			iterate = iterate->next;
	}
	free(key);
	return (NULL);
}

void	join_value(char *temp, const char *s, int *j)
{
	int	i;

	i = 0;
	while (s[i])
		temp[(*j)++] = s[i++];
	temp[*j] = '\0';
}

// echo hhhhhhhhhhhhhhhhhhhh"$USER"$USER

t_token	*expand_value(t_token *token)
{
	t_token	*iterate;
	char	*s;
	char	*temp;
	char *l;
	int i, j, k, n;

	iterate = token;
	while (iterate)
	{
		if (find_dollar(iterate->token) && iterate->type != DELIMITER)
		{
			iterate->expanded = 1;
			i = 0;
			j = 0;
			temp = malloc(ALLOC);
			if (!temp)
				return (NULL);
			while (iterate->token[i])
			{
				if (iterate->token[i] == '"')
				{
					temp[j++] = iterate->token[i++];
					while (iterate->token[i] && iterate->token[i] != '"')
					{
						if (iterate->token[i] == '$')
						{
							if (iterate->token[i + 1] == '"'
								|| !iterate->token[i + 1] || iterate->token[i
								+ 1] == '$' || (!ft_is_alpha(iterate->token[i
										+ 1]) && iterate->token[i + 1] != '?'
									&& iterate->token[i + 1] != '_'))
								temp[j++] = iterate->token[i++];
							else
							{
								i++;
								if (iterate->token[i] >= '0'
									&& iterate->token[i] <= '9')
								{
									i++;
									continue ;
								}
								s = malloc(ft_strlen(&iterate->token[i]) + 1);
								if (!s)
									return (NULL);
								k = 0;
								if (iterate->token[i] == '?')
								{
									i++;
									l = ft_itoa(g_status()->status);
									n = 0;
									while (l[n])
										temp[j++] = l[n++];
									free(l);
								}
								else
								{
									while (iterate->token[i]
										&& (ft_is_alpha(iterate->token[i])
											|| iterate->token[i] == '_')
										&& !is_special(iterate->token[i]))
										s[k++] = iterate->token[i++];
								}
								s[k] = '\0';
								s = expand_env(s);
								if (s)
								{
									join_value(temp, s, &j);
									free(s);
								}
							}
						}
						else
							temp[j++] = iterate->token[i++];
					}
					if (iterate->token[i] == '"')
						temp[j++] = iterate->token[i++];
				}
				else if (iterate->token[i] == '\'')
				{
					temp[j++] = iterate->token[i++];
					while (iterate->token[i] && iterate->token[i] != '\'')
						temp[j++] = iterate->token[i++];
					if (iterate->token[i] == '\'')
						temp[j++] = iterate->token[i++];
				}
				else if (iterate->token[i] == '$')
				{
					if (!iterate->token[i + 1] || iterate->token[i + 1] == '$'
						|| (!ft_is_alpha(iterate->token[i + 1])
							&& iterate->token[i + 1] != '?' && iterate->token[i
							+ 1] != '_' && iterate->token[i + 1] != '\''
							&& iterate->token[i + 1] != '"'
							&& !ft_isdigit(iterate->token[i])))
						temp[j++] = iterate->token[i++];
					else
					{
						i++;
						if (iterate->token[i] >= '0'
							&& iterate->token[i] <= '9')
						{
							i++;
							continue ;
						}
						else
						{
							s = malloc(ft_strlen(&iterate->token[i]) + 1);
							if (!s)
								return (NULL);
							k = 0;
							if (iterate->token[i] == '?')
							{
								i++;
								l = ft_itoa(g_status()->status);
								n = 0;
								while (l[n])
									temp[j++] = l[n++];
								free(l);
							}
							else
							{
								while (iterate->token[i]
									&& (ft_is_alpha(iterate->token[i])
										|| iterate->token[i] == '_')
									&& !is_special(iterate->token[i]))
									s[k++] = iterate->token[i++];
							}
							s[k] = '\0';
							s = expand_env(s);
							if (s)
							{
								join_value(temp, s, &j);
								free(s);
							}
						}
					}
				}
				else
					temp[j++] = iterate->token[i++];
			}
			temp[j] = '\0';
			free(iterate->token);
			iterate->token = ft_strndup(temp, ft_strlen(temp));
			free(temp);
		}
		iterate = iterate->next;
	}
	return (token);
}

int check_quote(char *delimiter)
{
	int i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '"' || delimiter[i] == '\'')
			return 1;
		else
			i++;
	}
	return 0;
}


t_token *join_token(t_token *token)
{
	t_token *iterate;
	t_token *next;
	t_token *new = NULL ;
	t_token *list = NULL;

	iterate = token;
	while (iterate)
	{
		if (iterate->expanded && (iterate->token[0] == '\0'))
		{
			next = iterate->next;
			ft_lstdelone(iterate, free);
			iterate = next;
			continue;
		}
		new = new_element(iterate->token);
		new->type = iterate->type;
		if (new->type == DELIMITER)
		{
			if (check_quote(new->token))
				new->heredoc = 1;
			else
				new->heredoc = 0;
		}
		ft_lstadd_back(&list, new);
		next = iterate->next;
		free(iterate);
		iterate = next;
	}
	return (list);
}


t_token	*expantion(t_token *token)
{
	token = expand_value(token);
	token = expand_wildcard(token);
	token = join_token(token);
	token = handle_quote(token);
	return (token);
}
