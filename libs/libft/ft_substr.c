/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:30:15 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/11 11:40:30 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = malloc(sizeof (char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0')
		sub[i++] = s[start ++];
	sub[i] = '\0';
	return (sub);
}

/* int	main(void)
{
	printf("%s",ft_substr("hola",3,1));
} */
