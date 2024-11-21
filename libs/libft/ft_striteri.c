/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:03:59 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/15 12:53:32 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}
/* void to_upper(unsigned int n, char *c)
{
	(void)n;
	if(*c >= 'a' && *c <= 'z')
		*c = *c - 32;
}
int main()
{
	char str[] = "hola mundo";
	ft_striteri(str, to_upper);
	printf("%s", str);
	return(0);
} */