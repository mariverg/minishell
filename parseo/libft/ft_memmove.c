/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:09:32 by mariverg          #+#    #+#             */
/*   Updated: 2023/12/05 11:46:56 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char		*s1;
	const unsigned char	*s2;

	s1 = (unsigned char *)dest;
	s2 = (const unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (s2 < s1)
	{
		while (len-- > 0)
			s1[len] = s2[len];
	}
	else if (s1 < s2)
		ft_memcpy(dest, src, len);
	return (dest);
}

/*int	main(void) {
	char str1[14] = "hola,mundo";
	char str2[10];

	ft_memmove(str2, str1, 5);

	printf("El contenido de str2 es: %s\n", str2);

	return (0);
}*/
