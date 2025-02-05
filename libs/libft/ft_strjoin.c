/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:45:20 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/18 13:04:58 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*ptr;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	len = (ft_strlen (s1)) + (ft_strlen (s2));
	ptr = malloc (sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1[i])
		ptr[j++] = s1[i++];
	i = 0;
	while (s2[i])
		ptr[j++] = s2[i++];
	ptr[j] = '\0';
	return (ptr);
}
/* int main()
{
	char *c1 = "hola, ";
	char *c2 = "mundo";
	char *c3 = ft_strjoin(c1, c2);

	if ((c3))
	{
		printf("%s", c3);
		free(c3);
	}
	else
		printf("failed");
	return (0);
} */