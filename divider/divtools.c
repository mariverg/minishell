#include "divider.h"

int istruncker(char c, char *comp)
{
	while (*comp)
	{
		if(c == *comp)
			return (1);
		comp++;
	}
	return (0);
}

int getspacer(char *c, char *comp)
{
	int one;
	int two;
	int i;

	i = 0;
	one = -1;
	two = -1;
	while (c[i])
	{
		if (c[i] == '\'' && two == -1)
		{
			one = -one;
		}
		if (c[i] == '\"' && one == -1)
		{
			two = -two;
		}
		if (istruncker(c[i], comp) && one == -1 && two == -1)
		{
			return (i);
		}
		i++;
	}
	return (i);
}


void prntchunks(t_list *tl)
{
	while(tl)
	{
		printf("un chunk %s\n", (char *)tl->content);
		tl = tl->next;
	}
}

// t_list *addchunk(t_list *onepiece, char *c, int start, int end)
// {
// 	// printf("anhadiendo de %s desde %i hasta %i\n", c, start, end);
// 	if (!onepiece)
// 	{
// 		onepiece = ft_lstnew(ft_substr(c, start, end));
// 	}
// 	else
// 	{
// 		ft_lstlast(onepiece)->next = ft_lstnew(ft_substr(c, start, end));
// 	}
// 	return (onepiece);
// }