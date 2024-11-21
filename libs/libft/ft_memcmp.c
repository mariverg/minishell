/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:18:36 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/08 13:46:11 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	size_t				i;

	if (n == 0)
		return (0);
	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}
/* int main()
{
	char str1[] = "hola mu";
	char str2[] = "hola mundo";
	int j = ft_memcmp(str1, str2, sizeof(str1));
	if (j < 0)
	printf("str1 es menor que str2\n");
	else if (j > 0)
	printf("str1 es mayor que str2\n");
	else
	printf("str1 es igual que str2\n");
	return (0);
} */