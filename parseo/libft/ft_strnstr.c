/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 07:46:25 by mariverg          #+#    #+#             */
/*   Updated: 2023/12/12 08:16:31 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*to_find)
		return ((char *)str);
	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] == to_find[0])
		{
			j = 0;
			while (str[i + j] == to_find[j] && i + j < len)
			{
				if (to_find[j + 1] == '\0')
					return ((char *)&str[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
/* int main(void)
{
	const char *str = "hola, como estas";
	const char *to_find = "hola";
	size_t len = 5;

	char *result = ft_strnstr(str, to_find, len);

	if (result != NULL)
		printf("\"%s\" fue encontrado en la cadena \"%s\".\n", to_find, str);
	else
		printf("\"%s\" no se encuentra en la cadena \"%s\".\n", to_find, str);
	return 0;
} */