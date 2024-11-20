/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 08:29:35 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/16 13:05:03 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	char		*ptr;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	ptr = malloc(sizeof(char) * (end - start + 1));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, &s1[start], end - start + 1);
	ptr[end - start] = '\0';
	return (ptr);
}
/* int main()
{
	char *str = "muhola mundooo!mumumu";
	char *set = "mu";
	char *c = ft_strtrim(str, set);

	if(c)
	{	printf("%s\n", c);
		free(c);
	}
	else
		printf("failed");
	return(0);
} */