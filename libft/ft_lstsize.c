#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"
int	ft_lstsize(t_execution *lst)
{
	int	counter;
	counter = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		counter++;
	}
	return (counter);
}
int	ft_lstsize_envp(t_envp *linkedList)
{
	int	counter;
	counter = 0;
	t_envp *lst = linkedList;
	while (lst)
	{
		lst = lst->next;
		counter++;
	}
	return (counter);
}
