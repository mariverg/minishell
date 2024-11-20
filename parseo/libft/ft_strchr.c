/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:00:42 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/16 13:21:01 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *src, int c)
{
	char	s;

	s = (char)c;
	while ((*src != '\0') && (*src != s))
		src++;
	if (*src == s)
		return ((char *)src);
	return (NULL);
}

/*int	main(void)
{
	char str[] = "Hola mundo";
	char	*ptr = ft_strchr(str, 'u');

	if (ptr != NULL)
		printf("El carácter 'u' se encuentra en la posición: %ld\n", ptr - str);
	else
		printf("El carácter 'u' no se encuentra en la cadena.\n");
	return (0);
}*/