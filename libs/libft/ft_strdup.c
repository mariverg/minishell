/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:51:48 by mariverg          #+#    #+#             */
/*   Updated: 2023/12/15 10:45:42 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s1) + 1;
	dup = malloc(len);
	if (dup != NULL)
		ft_memcpy(dup, s1, len);
	return (dup);
}
/* int main() {
	const char *s = "Hello, World!";
	char *dest = ft_strdup(s);
	printf("%s\n", dest);
	free(dest);
	return (0);
} */