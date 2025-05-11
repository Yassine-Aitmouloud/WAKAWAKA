#include "../includes/minishell.h"
#include "../includes/tokenizer.h"
#include "../includes/libft.h"

char *searchAndsave(char *var)
{
	t_envp *tmp = new_envp;
	while(tmp)
	{
		if(strncmp(var,tmp->key,ft_strlen(var)) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return NULL;
}

int	search_in_env(char *var)
{
	t_envp *tmp = new_envp;
	while(tmp)
	{
		if(strncmp(var,tmp->key,ft_strlen(var)) == 0)
			return (1);
		tmp = tmp->next;
	}
	return 0;
}
int	change_in_env(char *var,char *buf)
{
	t_envp *tmp = new_envp;
	while(tmp)
	{
		if(strncmp(var,tmp->key,ft_strlen(var)) == 0)
		{
			free(tmp->value);
			tmp->value = buf;
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}



int CountLenKey(char *line)
{
	int count = 0;
	while (line[count] && line[count] != '=' && !(line[count] == '+' && line[count + 1] == '='))
		count++;
	return (count);
}

void	ft_chdir(t_execution *input)
{
	if (!input->args[1])
	{
		if (search_in_env("HOME") == 1)
		{
			change_in_env("OLDPWD",getcwd(NULL,0));
			chdir(searchAndsave("HOME"));
			change_in_env("PWD",getcwd(NULL,0));
		}
		else
			printf("%s\n","cd: HOME not set");
	}
	else
	{
		change_in_env("OLDPWD",getcwd(NULL,0));
		chdir(input->args[1]);
		change_in_env("PWD",getcwd(NULL,0));
	}
}

void	ft_echo(t_execution *input)
{
	int i;
	i = 1;
	int flag = 1;
	
	if (input->args[1])
	{
		if (strncmp(input->args[1], "-n", 2) == 0)
		{
			flag = 0;
			i++;
		}
	}
	else
		printf("\n");
	while (input->args[i])
	{
		ft_putstr_fd(input->args[i], 1);
		if (flag == 1 && input->args[i + 1] == NULL)
			ft_putchar_fd('\n', 1);
		if (input->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

void	ft_env()
{
	t_envp *tmp = new_envp;
	while (tmp)
	{
		if (tmp->key && tmp->value != NULL)
			printf("%s=%s\n", tmp->key,tmp->value);
		tmp = tmp->next;
	}
}

t_envp	*AddToList(char *line)
{
	t_envp *node;
	int LenKey;
	LenKey = CountLenKey(line);
	node = malloc(sizeof(t_envp));
	if (!node)
		return NULL;
	node->key = ft_strndup(line,LenKey);
	if (line[LenKey] == '=' && line[LenKey + 1] != '\0')
	{
		node->value = ft_strndup(line + LenKey + 1, ft_strlen(line) - LenKey + 1);
	}
	else
		node->value = ft_strdup("");
	node->next = NULL;
	return(node);
}

int	already_in(char *arg)
{
	t_envp	*tmp = new_envp;
	char	*key;
	char	*new_value;
	int		lenKey;
	int		append = 0;
	lenKey = CountLenKey(arg);
	if (arg[lenKey] == '+' && arg[lenKey + 1] == '=')
		append = 1;
	key = ft_strndup(arg, lenKey);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, lenKey) == 0 && tmp->key[lenKey] == '\0')
		{
			if (append)
				new_value = ft_strjoin(tmp->value, arg + lenKey + 2); 
			else
				new_value = ft_strdup(arg + lenKey + 1); 

			free(tmp->value);
			tmp->value = new_value;
			free(key);
			return (1);
		}
		tmp = tmp->next;
	}
	free(key);
	return (0);
}
int	check_sen(char *list)
{
	int j = 0;
	if ((list[0] != '_') && (!ft_isalpha(list[0])))
		return 0;
	while(list[j] && list[j] != '=')
	{
		if (list[j] == '+' && list[j + 1] == '=')
		{
			j++;
		}
		if ((ft_isalnum(list[j]) == 0) && list[j] != '=')
			return 0;
		j++;
	}
	return 1;
}
void ft_export(t_execution *list)
{
	int i;
	i = 1;
	t_envp *node;
	t_envp *export = new_envp;
	while(list->args[i])
	{
		if (check_sen(list->args[i]) == 0)
		{
			printf("bash: export: `%s': not a valid identifier\n",list->args[i]);
			i++;
		}
		else if (already_in(list->args[i]) == 1)
			i++;
		else
		{
			node = new_element2(list->args[i]);
			ft_lstadd_back2(&new_envp,node);	
			i++;
		}
	}
	if (!list->args[1])
	{
		while(export)
		{
			if (export->key && export->value)
				printf("declare -x %s=\"%s\"\n", export->key, export->value);
			else if (export->key)
				printf("declare -x %s\n", export->key);
			export = export->next;
		}
	}
}
int if_builtin(char *cmd)
{
    if (!ft_strcmp(cmd, "export") )
        return 1;
    else if (!ft_strcmp(cmd, "unset"))
        return 1;
    else if (!ft_strcmp(cmd, "pwd"))
        return 1;
    else if (!ft_strcmp(cmd, "env"))
        return 1;
    else if (!ft_strcmp(cmd, "exit"))
        return 1;

	else if (!ft_strcmp(cmd,"cd"))
		return 1;

	else if (!ft_strcmp(cmd,"echo"))
		return 1;
	else if(!ft_strcmp(cmd,"exit"))
		return 1;
    return 0;
}

void	is_builtin(char *cmd,t_execution *list,int size)
{
	if (!ft_strcmp(cmd, "export"))
		ft_export(list);
	if (!ft_strcmp(cmd, "unset"))
		ft_unset(list);
	if (!ft_strcmp(cmd, "pwd"))
		ft_pwd();
	if (!ft_strcmp(cmd, "env"))
		ft_env();
	if (!ft_strcmp(cmd,"echo"))
		ft_echo(list);
	if (!ft_strcmp(cmd,"cd"))
		ft_chdir(list);
	if (!ft_strcmp(cmd, "exit"))
		ft_exit(list,size);
}

void ft_unset(t_execution *list)
{
    t_envp *prev = NULL;
    t_envp *current;
    int (i) = 1;
    while (list->args[i]) 
    {
        current = new_envp;
        prev = NULL;
        while (current) 
        {
            if (!ft_strncmp(list->args[i], current->key , ft_strlen(list->args[i])) &&
                current->key[ft_strlen(list->args[i])] == '\0') 
            {
                if (prev == NULL) 
                    new_envp = current->next;
                else 
                    prev->next = current->next;
                free(current->key);
                free(current->value);
                free(current);
                break;
            }
            prev = current;
            current = current->next;
        }
        i++;
    }
}
int checkIfNum(char *number)
{
	int j = 0;
	int i = 0;
	if (!number)
		exit(g_status()->status >> 8);
	while(number[i])
	{
		if (number[j] >= 48 && number[j] >= 57)
			j++;
		i++;
	}
	if (j == i)
		return 1;
	else
		return 0;
}
void	ft_exit(t_execution *input,int size)
{
	int status;
	status = 0;
	if (size == 1)
		printf("%s\n","exit");
	if (checkIfNum(input->args[1]))
	{
		printf("bash: exit: %s: numeric argument required\n",input->args[1]);
		exit(2);
	}
	else if (input->args[2])
	{
		printf("bash: exit: too many arguments\n");
		g_status()->status = 1;
	}
	else if (input->args[1])
	{
		status = ft_atoi(input->args[1]);
		exit (status);
	}
	exit(g_status()->status >> 8);
}

void	ft_pwd()
{
	char *buf;
	buf = getcwd(NULL, 0);
	if (!buf)
		printf("%s\n",searchAndsave("PWD"));
	else
		printf("%s\n", buf);
	free(buf);
}

char	**listToArray()
{
	int size;
	char *tmp;
	int i = 0;
	char **envpExecve;
	size = ft_lstsize_envp(new_envp);
	envpExecve = malloc(sizeof(char *) * (size + 1));
	t_envp *head = new_envp;
	while(head)
	{
		tmp = ft_strjoin(head->key,"=");
		envpExecve[i] = ft_strjoin(tmp,head->value);
		i++;
		free(tmp);
		head = head->next;
	}
	envpExecve[i] = NULL;
	return(envpExecve);
}

t_envp *ft_create_envp(char **envp)
{
    int i = 0;
    t_envp *head = NULL;
    t_envp *node;
    if (!envp)
        return (NULL);
   while (envp[i])
	{
		node = new_element2(envp[i]);
		if (!node)
		{
			while (head)
			{
				t_envp *tmp = head->next;
				free(head);
				head = tmp;
			}
			return (NULL);
		}
		ft_lstadd_back2(&head, node);
		i++;
	}
    return (head);
}

t_envp *new_element2(char *line)
{
    char *key;
	t_envp *new;
    if (!line)
        return NULL;
    int lenKey = CountLenKey(line);
	key = ft_strndup(line, lenKey);
    char *value = NULL;
    if (line[lenKey] == '=')
    {
        if (line[lenKey + 1] != '\0')
            value = ft_strdup(line + lenKey + 1);
        else
            value = ft_strdup("");
	}
	if (line[lenKey] == '+')
	{
		if (line[lenKey + 2] != '\0')
            value = ft_strdup(line + lenKey + 2);
        else
            value = ft_strdup("");	
	}
    new = malloc(sizeof(t_envp));
    if (!new)
    {
        free(key);
        free(value);
        return NULL;
    }
    new->key = key;
    new->value = value;
    new->next = NULL;
    return new;
}

t_envp	*ft_lstlast2(t_envp *lst)
{
	t_envp	*last_content;

	if (!lst)
		return (NULL);
	last_content = lst;
	while (last_content != NULL && last_content->next != NULL)
	{
		last_content = last_content->next;
	}
	return (last_content);
}

void	ft_lstadd_back2(t_envp **lst, t_envp *new)
{
	t_envp	*last;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast2(*lst);
		last->next = new;
	}
}
