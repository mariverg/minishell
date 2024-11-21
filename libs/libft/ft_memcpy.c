/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 08:54:14 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/09 12:42:16 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*s1;
	const unsigned char	*s2;
	size_t				i;

	s1 = (unsigned char *)dest;
	s2 = (unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (s1);
}

/*int	main(void)
{
	char s1[14] = "hola mundo";
	char s2[14];

	ft_memcpy(s2, s1, 6);

	printf("El contenido de s2 es: %s\n", s2);

	return (0);
}*/