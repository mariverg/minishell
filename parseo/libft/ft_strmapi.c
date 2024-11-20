/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:50:02 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/16 12:29:19 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*result;

	len = ft_strlen(s);
	if (s == NULL || f == NULL)
		return (NULL);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[len] = '\0';
	return (result);
}
/* char	to_lower(unsigned int i, char c)
{
	if (i % 2 == 0 && c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}
int main()
{
	char str[] = "HOLA MUNDO";
	char *c = ft_strmapi(str, to_lower);
	printf("%s", c);
	free(c);
	return(0);
} */