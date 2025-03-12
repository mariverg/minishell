/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 08:40:14 by mariverg          #+#    #+#             */
/*   Updated: 2023/12/15 10:46:31 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	start;

	dest_len = ft_strlen(dest);
	if (dstsize == 0 || dstsize < dest_len)
		start = dstsize;
	else
		start = dest_len;
	return (start + ft_strlcpy(dest + start, src, dstsize - start));
}

/*int main() {
	char dest[30] = "hola";
	const char src[30] = "mundo";

	size_t result = ft_strlcat(dest, src, 8);
	printf("El resultado de concatenar las cadenas es: %s\n", dest);
	printf("La longitud total de la cadena concatenada es: %zu\n", result);
	return (0);
}*/