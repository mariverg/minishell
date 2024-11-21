/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:20:56 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/16 12:40:57 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && (*s1 || *s2))
	{
		if (*s1 != *s2)
			return ((unsigned char) *s1 - (unsigned char) *s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
/* int main()
{
	char *str1 = "hola mundo";
	char *str2 = "hola mundo";
	size_t n = 6;
	int result = ft_strncmp(str1, str2, n);
	if(result < 0)
		printf("str1 es menor a str2");
	else if (result > 0)
		printf("str1 es mayor a str2");
	else 
		printf("str1 es igual a str2");
	return(0);
} */