/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:26:38 by mariverg          #+#    #+#             */
/*   Updated: 2023/12/15 10:46:51 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *src, int c)
{
	int		i;
	char	s;

	s = (char)c;
	i = ft_strlen(src);
	while (i >= 0)
	{
		if (src[i] == s)
			return ((char *)&src[i]);
		i--;
	}
	return (NULL);
}

/*int	main(void)
{
	char str[] = "Hola mundooaaaa";
	char *ptr = ft_strrchr(str, 'a');

	if (ptr != NULL)
	{
		printf("La última aparición del carácter 'a'
		se encuentra en la posición:%ld\n", ptr - str);
	}
	else
	{
		printf("El carácter 'a' no se encuentra en la cadena.\n");
	}
	return (0);
}*/