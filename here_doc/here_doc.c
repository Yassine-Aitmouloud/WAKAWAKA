/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:13:17 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/19 19:05:00 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

char	*file_name(void)
{
	static int	i = 0;
	char		*join;

	join = ft_strjoin(HERE_DOC_FILE, ft_itoa(i));
	while (!access(join, F_OK))
	{
		i++;
		join = ft_strjoin(HERE_DOC_FILE, ft_itoa(i));
	}
	return (join);
}

void	here_doc_handler(int i)
{
	(void)i;
	g_status()->status = 130;
	g_status()->interuppeted = 1;
	write(2, "\n", 1);
	close(STDIN_FILENO);
}

pid_t	fork_here_doc(void)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		signal(SIGINT, here_doc_handler);
	return (pid);
}

int	read_here_doc(int fd, char *delimiter)
{
	char	*input;
	pid_t	pid;

	pid = fork_here_doc();
	if (pid == 0)
	{
		while (!g_status()->interuppeted)
		{
			input = readline("here_doc $-> : ");
			if (!input)
				exit(g_status()->status);
			else if (ft_strlen(delimiter) == ft_strlen(input)
				&& !ft_strncmp(delimiter, input, ft_strlen(delimiter)))
				break ;
			ft_putstr_fd(input, fd);
			ft_putchar_fd('\n', fd);
		}
		g_status()->status = 0;
		exit(g_status()->status);
	}
	else
	{
		waitpid(pid, &g_status()->status, 0);
		if (WIFEXITED(g_status()->status))
		{
			g_status()->status = WEXITSTATUS(g_status()->status);
            if (g_status()->status == 130)
            {
                printf("test 1\n");
                return 1;
            }
			return 0;
		}
	}
    return 0;
}

t_token	*handle_heredoc(t_token *tokens)
{
	t_token	*iterate;
	char	*file_nm;
	int		fd;

	iterate = tokens;
	while (iterate)
	{
		while (iterate && iterate->type != HERE_DOC)
        {
			    iterate = iterate->next;
        }
		if (iterate && iterate->type == HERE_DOC)
		{
			free(iterate->token);
			iterate->token = ft_strndup("<", 1);
			iterate->type = RED_IN;
			iterate = iterate->next;
			file_nm = file_name();
			fd = open(file_nm, O_CREAT | O_RDWR, 0666);
            if (read_here_doc(fd, iterate->token))
                return NULL;
            free(iterate->token);
            iterate->token = ft_strndup(file_nm, ft_strlen(file_nm));
            close(fd);
		}
        else {
            if (iterate && iterate->next)
            iterate = iterate->next;
        }
	}
	return (tokens);
}
