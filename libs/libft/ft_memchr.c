/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:59:03 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/08 13:16:21 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t				i;
	const unsigned char	*s;
	unsigned char		ch;

	s = (const unsigned char *)str;
	ch = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (s[i] == ch)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
/* int  main()
{
	char str[] = "hola mundo";
	char c = 'n';
	char *p = ft_memchr(str, c, sizeof(str));
	if (p)
		printf("'%c' la posicion es: %ld\n", c, p -str);
	else
		printf("'%c' not found\n", c);
	return (0);
} */