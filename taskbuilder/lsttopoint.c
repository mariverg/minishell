#include "../minishell.h"

char **getargs(t_list *tl)
{
	char **res;
	int i;
	int j;
	t_list *copy;

	i = 0;
	copy = tl;
	while (copy)
	{
		i++;
		copy = copy->next;
	}
	res = malloc(sizeof(char *) * (i + 1));
	j = 0;
	copy = tl;
	while (j < i)
	{
		res[j] = copy->content;
		copy = copy->next; 
		j++;
	}
	res[j] = 0;
	return(res);
}