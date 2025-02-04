#include "divider.h"

t_list	*getchunks(char *c)
{
	int		i;
	int		startpoint;
	int		endpoint;
	t_list	*pointer;
	t_list	*firstnode;

	firstnode = malloc(sizeof(t_list));
	firstnode->next = 0;
	pointer = firstnode;
	startpoint = 0;
	endpoint = ft_strlen(c);
	i = 0;
	while (i < endpoint)
	{
		i += getspacer(&c[i], "|");
		pointer->next = malloc(sizeof(t_list));
		pointer = pointer->next;
		pointer->content = ft_substr(c, startpoint, i - startpoint);
		pointer->next = 0;
		i++;
		startpoint = i;
	}
	pointer = firstnode->next;
	free(firstnode);
	return (pointer);
}

t_comand	*makecomands(char *c)
{
	t_comand	*firstnode;
	t_comand	*pointer;
	t_list		*rawproceses;
	t_list		*trash;

	if (!c)
		return (0);
	firstnode = malloc(sizeof(t_comand));
	firstnode->next = 0;
	pointer = firstnode;
	rawproceses = getchunks(c);
	trash = rawproceses;
	while (rawproceses)
	{
		pointer->next = getcom(rawproceses->content);
		rawproceses = rawproceses->next;
		pointer = pointer->next;
		pointer->next = 0;
	}
	pointer = firstnode->next;
	free(firstnode);
	freelst(trash);
	return (pointer);
}
